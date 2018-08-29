#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include "system.h"

esp_err_t KairOS_system_init(void)
{
    printf("System initiated!\n");    
    return 1;
}