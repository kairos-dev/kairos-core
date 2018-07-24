#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include "storage.h"

esp_err_t storage_init(void)
{
    printf("Storage initiated!\n");    
    return 1;
}