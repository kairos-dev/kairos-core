#include "rtc.h"
#include "def/board.h"

static const char *TAG = "RTC";

i2c_dev_t rtc_dev;

kairos_err_t init_rtc(void) {
  KAIROS_LOGI(TAG, "Initializing RTC");

  memset(&rtc_dev, 0, sizeof(i2c_dev_t));

  while (pcf8563_init_desc(&rtc_dev, 0, PIN_SDA, PIN_SCL) != KAIROS_ERR_OK)
    {
        KAIROS_LOGE(TAG, "Could not init device descriptor\n");
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
  
  return KAIROS_ERR_OK;
}


