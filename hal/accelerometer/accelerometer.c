#include "accelerometer.h"
#include "def/board.h"

static const char *TAG = "ACCELEROMETER";

i2c_dev_t acc_dev;

struct bma4_dev bma;

int8_t accelerometer_i2c_read(uint8_t reg_addr,  uint8_t *reg_data, uint32_t length, void* intf_ptr) {
    KAIROS_LOGD(TAG, "Reading data: address %d, data %d", reg_addr, *reg_data);

    I2C_DEV_TAKE_MUTEX(&acc_dev);
    I2C_DEV_CHECK(&acc_dev, i2c_dev_read_reg(&acc_dev, reg_addr, reg_data, length));   
    I2C_DEV_GIVE_MUTEX(&acc_dev);
    KAIROS_LOGD(TAG, "Result: data %d", *reg_data);
    return KAIROS_ERR_OK;
}

int8_t accelerometer_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void* intf_ptr) {
    KAIROS_LOGD(TAG, "Writing data: address %d, data %d", reg_addr, *reg_data);
    I2C_DEV_TAKE_MUTEX(&acc_dev);
    I2C_DEV_CHECK(&acc_dev, i2c_dev_write_reg(&acc_dev, reg_addr, reg_data, length));
    I2C_DEV_GIVE_MUTEX(&acc_dev);
    return KAIROS_ERR_OK;
}

void accelerometer_delay_us(uint32_t period_ns, void* intf_ptr) {
  vTaskDelay(period_ns / 1000 / portTICK_PERIOD_MS);
}

kairos_err_t init_accelerometer(void) {
  KAIROS_LOGI(TAG, "Initializing Accelerometer");
  memset(&acc_dev, 0, sizeof(i2c_dev_t));

  while (bma423_init_desc(&acc_dev, 1, PIN_SDA, PIN_SCL) != KAIROS_ERR_OK)
  {
      KAIROS_LOGE(TAG, "Could not init device descriptor\n");
      vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  KAIROS_LOGI(TAG, "Reseting Accelerometer");
  uint8_t data = BMA4_SOFT_RESET;
  accelerometer_i2c_write(BMA4_CMD_ADDR, &data, 1, NULL);

  vTaskDelay(10 / portTICK_PERIOD_MS);

  bma.intf = BMA4_I2C_INTF;
  bma.intf_ptr = &bma; // intf_ptr must be set to non-NULL for some reason
  bma.read_write_len = 8;
  bma.resolution = 12;
  bma.bus_read = accelerometer_i2c_read;
  bma.bus_write = accelerometer_i2c_write;
  bma.delay_us = accelerometer_delay_us;
  bma.feature_len = BMA423_FEATURE_SIZE;

  int16_t result;
  if((result = bma423_init(&bma))) {
    KAIROS_LOGE(TAG, "bma423_init failed %i", result);
    return KAIROS_ERR_FAIL;
  }

  if((result = bma423_write_config_file(&bma))) {
    KAIROS_LOGE(TAG, "bma423_write_config_file failed %i\n", result);
    return KAIROS_ERR_FAIL;
  }
  //
  if ((result = bma4_set_accel_enable(1, &bma))) {
    KAIROS_LOGE(TAG, "bma4_set_accel_enable failed %i\n", result);
    return KAIROS_ERR_FAIL;
  }

  struct bma423_axes_remap remap_data;

  remap_data.x_axis = 1;
  remap_data.x_axis_sign = 0xFF;
  remap_data.y_axis = 0;
  remap_data.y_axis_sign = 0xFF;
  remap_data.z_axis = 2;
  remap_data.z_axis_sign = 0xFF;

  if((result = bma423_set_remap_axes(&remap_data, &bma))) {
    KAIROS_LOGE(TAG, "bma423_set_remap_axes failed %i\n", result);
    return KAIROS_ERR_FAIL;
  }
  
  if((result = bma423_feature_enable(BMA423_STEP_CNTR, 1, &bma))) {
    KAIROS_LOGE(TAG, "bma423_feature_enable step_count failed %i\n", result);
    return KAIROS_ERR_FAIL;
  }

  if((result = bma423_feature_enable(BMA423_WRIST_WEAR, 1, &bma))) {
    KAIROS_LOGE(TAG, "bma423_feature_enable wrist_wear failed %i\n", result);
    return KAIROS_ERR_FAIL;
  } 

  // First, configure the pin to interrupt output
  struct bma4_int_pin_config int_config;
  int_config.input_en = BMA4_INPUT_DISABLE;
  int_config.output_en = BMA4_OUTPUT_ENABLE;
  int_config.lvl = BMA4_ACTIVE_HIGH;
  // internal pullup and pulldown resistors of ESP32 are disabled during deep sleep
  // (see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html#external-wakeup-ext1 )
  // Therefore the BMA needs to use it's push-pull pin capability to ensure defined logic level
  int_config.od = BMA4_PUSH_PULL;
  int_config.edge_ctrl = BMA4_LEVEL_TRIGGER;
  if((result = bma4_set_int_pin_config(&int_config, BMA4_INTR1_MAP, &bma))) {
    printf("bma4_set_int_pin_config failed: %i\n", result);
  }

  if ((result = bma423_map_interrupt(BMA4_INTR1_MAP, BMA423_WRIST_WEAR_INT, 1, &bma))) {
    printf("bma423_map_interrupt %i\n", result);
  }
  
  //TODO: Fix the bit mask.
  // gpio_config_t pin_config;
  // pin_config.pin_bit_mask = ACC_INT_1_GPIO;
  // pin_config.mode = GPIO_MODE_INPUT;
  // pin_config.pull_up_en = GPIO_PULLUP_DISABLE;
  // pin_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
  // pin_config.intr_type = GPIO_INTR_DISABLE;

  // gpio_config(&pin_config);

  struct bma4_err_reg error_reg;
  if((result = bma4_get_error_status(&error_reg, &bma))) {
    KAIROS_LOGE(TAG, "bma4_get_error_status failed %i\n", result);
    return KAIROS_ERR_FAIL;
  }

  if(error_reg.fatal_err || error_reg.cmd_err) {
    KAIROS_LOGE(TAG,
        "bma has error state set:\nerror_reg.fatal_err: %i\nerror_reg.cmd_err: %i\n",
        error_reg.fatal_err,
        error_reg.cmd_err);
    return KAIROS_ERR_FAIL;
  }
  
  return KAIROS_ERR_OK;
}

uint8_t step_count_accelerometer(uint32_t *step_count) {
  int16_t result;
  if ((result = bma423_step_counter_output(step_count, &bma))) {
    KAIROS_LOGE(TAG, "Reading step counter failed: bma423_step_counter_output %i\n", result);
    return KAIROS_ERR_FAIL;
  }
  return KAIROS_ERR_OK;
}

uint8_t get_axis_accelerometer(struct bma4_accel *axis) {
  int16_t result;
  if ((result = bma4_read_accel_xyz(axis, &bma))) {
    KAIROS_LOGE(TAG, "Reading axis failed: bma423_get_remap_axes %i\n", result);
    return KAIROS_ERR_FAIL;
  }
  return KAIROS_ERR_OK;
}

uint8_t get_int_status_accelerometer(uint16_t *int_status) {
  int16_t result;
  if ((result = bma423_read_int_status(int_status, &bma))) {
    KAIROS_LOGE(TAG, "Reading int status failed: bma423_read_int_status %i\n", result);
    return KAIROS_ERR_FAIL;
  }
  return KAIROS_ERR_OK;
}
