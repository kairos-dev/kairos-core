#include "i2c_rtc.h"
#include "def/board.h"

static const char *TAG = "TEST_I2C_RTC";

void task_i2c_rtc() {
    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));

    ESP_ERROR_CHECK(pcf8563_init_desc(&dev, 0, PIN_SDA, PIN_SCL));

    struct tm time = {
        .tm_year = 122,
        .tm_mon  = 8,  
        .tm_mday = 6,
        .tm_hour = 14,
        .tm_min  = 19,
        .tm_sec  = 44,
        .tm_wday = 0    
    };
    ESP_ERROR_CHECK(pcf8563_set_time(&dev, &time));

    while (1)
    {
        bool valid;
        esp_err_t r = pcf8563_get_time(&dev, &time, &valid);
        if (r == ESP_OK)
            KAIROS_LOGI(TAG, "%04d-%02d-%02d %02d:%02d:%02d, %s", time.tm_year + 1900, time.tm_mon + 1,
                time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec, valid ? "VALID" : "NOT VALID");
        else
            KAIROS_LOGE(TAG, "Error %d: %s", r, esp_err_to_name(r));


        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
