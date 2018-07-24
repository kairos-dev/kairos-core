#ifndef AUDIO_H_
#define AUDIO_H_

#include <stdint.h>
#include <freertos/FreeRTOS.h>

esp_err_t audio_init(void);

esp_err_t audio_set_volume(uint8_t volume);

uint8_t audio_get_volume(void);

#endif