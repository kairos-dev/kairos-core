#include "display.h"

static const char *TAG = "DISPLAY";

kairos_err_t init_display(void) {
  KAIROS_LOGI(TAG, "Initializing Display");

  while (init_gdeh0154d67() != KAIROS_ERR_OK)
    {
        KAIROS_LOGE(TAG, "Could not init display");
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
  
  return KAIROS_ERR_OK;
}


