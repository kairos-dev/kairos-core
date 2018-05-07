#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>
#include <sh1106.h>
#include <bmx280.h>
#include <hmc5883l.h>

#include "sdkconfig.h"

void app_main()
{
    xTaskCreate(hmc5883l_test, "hmc5883l_test", 4096, NULL, 5, NULL);
    xTaskCreate(&task_test_SSD1306i2c, "task_test_SSD1306i2c", 4096,NULL,4,NULL);
}
