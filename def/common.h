// Board
#include "def/board.h"

// Common
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <stdint.h>
#include <stdbool.h>
#include <driver/i2c.h>
#include "esp_timer.h"
#include "esp_pm.h"
#include "esp_log.h"

#define KAIROS_ERR_FAIL 1
#define KAIROS_ERR_OK 	0
#define KAIROS_INVALID_ARGS -1
#define KAIROS_TIMEOUT -2

#define OUTPUT 0
#define INPUT 1

#define ANALOG 1
#define DIGITAL 0

#define kairos_v 0.1.0

#define KAIROS_LOGE( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_ERROR,   tag, format, ##__VA_ARGS__)
#define KAIROS_LOGW( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_WARN,    tag, format, ##__VA_ARGS__)
#define KAIROS_LOGI( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO,    tag, format, ##__VA_ARGS__)
#define KAIROS_LOGD( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define KAIROS_LOGV( tag, format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

#define NOP() asm volatile ("nop")

unsigned long IRAM_ATTR micros();

void IRAM_ATTR delay_us(uint32_t us);

void IRAM_ATTR delay_ms(uint32_t delay);

typedef uint8_t kairos_err_t;
