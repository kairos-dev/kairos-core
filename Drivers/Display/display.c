#include <stdio.h>
#include "display.h"
#include <SSD1306.h>

#define PROTOCOL SSD1306_PROTO_I2C
#define ADDR     SSD1306_I2C_ADDR_0
#define SECOND (1000 / portTICK_PERIOD_MS)

#define I2C_BUS  0
#define SCL_PIN  4
#define SDA_PIN  0

static ssd1306_t dev;

void i2c0_init(void){
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}


kairos_err_t display_init(void)
{
    i2c_dev_t i2c_dev =
    {
        .bus = I2C_NUM_0,
        .addr = ADDR
    };

    /*Screen initialization*/
    i2c0_init();

    dev.i2c_dev = (lv_i2c_handle_t)i2c_dev;
    dev.protocol = PROTOCOL ; //SSD1306_PROTO_SPI3;
    dev.screen   = SSD1306_SCREEN; //SSD1306_SCREEN
    dev.width    = LV_HOR_RES;
    dev.height   = LV_VER_RES;
    // dev.rst_pin  = RST_PIN; //No RST PIN USED
    // ssd1306_command(&dev, 0xDA);

    while (ssd1306_init(&dev) != 0) {
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(SECOND);
        // return KAIROS_ERR_FAIL;
    }
    
    // ssd1306_set_whole_display_lighting(&dev, true);
    // ssd1306_set_scan_direction_fwd(&dev,true);
    ssd1306_set_scan_direction_fwd(&dev,false);
    ssd1306_set_inversion(&dev, false);
    // Flip display 180º
    ssd1306_set_segment_remapping_enabled(&dev, true);

    ssd1306_set_whole_display_lighting(&dev, false);
    // ssd1306_display_on(&dev, false);
    printf("Display initiated!\n");
    
    return KAIROS_ERR_OK;
}

kairos_err_t display_update(void)
{
    if(ssd1306_need_redraw())
    {
        ssd1306_load_frame_buffer(&dev);
        return KAIROS_ERR_OK;
    }

    return KAIROS_ERR_FAIL;
}