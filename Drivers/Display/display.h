#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <System/system.h>

kairos_err_t display_init(void);

kairos_err_t display_update(void);

kairos_err_t display_turn_off_light(void);

kairos_err_t display_turn_on_light(void);

void display_task(void *pvParameters);

#endif