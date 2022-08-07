#include "system.h" 

static const char *TAG = "SYSTEM";

kairos_err_t system_init(void)
{
    kairos_err_t passed = KAIROS_ERR_FAIL;
    
    // passed |= init_peripherals();
    passed |= init_modules();

    ESP_LOGI(TAG, "System initiated!");

    return passed;
}
