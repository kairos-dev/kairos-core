#include "test_accelerometer.h"
#include <stdint.h>

struct bma4_dev bma_test;

void task_step_count() {
  struct bma4_accel data;
  int16_t result;

  printf("Waiting for step counts!!!\n");
  while(1) {
    uint32_t step_out = 0;
    if ((result = step_count_accelerometer(&step_out))) {
      printf("bma423_step_counter_output %i\n", result);
    }

    uint16_t int_status;
    if ((result = get_int_status_accelerometer(&int_status))) {
      printf("bma423_read_int_status %i\n", result);
    }
    if (int_status & BMA423_WRIST_WEAR_INT) {
      printf("Wrist Wear!\n");
    }

    printf("Step counter output: %u\n", step_out);
    get_axis_accelerometer(&data);

    printf(
        "x = %d "
        "y = %d "
        "z  = %d\n",
        data.x,
        data.y,
        data.z);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}
