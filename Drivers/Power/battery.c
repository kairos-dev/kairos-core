#include "battery.h"

uint8_t battery_monitor_init(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(BATTERY_PIN, ADC_ATTEN_DB_11);
    return 0;
}

uint16_t get_battery_raw_voltage(void)
{
    return((adc1_get_raw(BATTERY_PIN)*3300)/4095);
}

uint16_t get_battery_mv(void)
{
    return ((RESISTOR1+RESISTOR2)*get_battery_raw_voltage())/(RESISTOR2);
}

uint8_t get_battery_porcentage(void)
{
    return (uint8_t)(get_battery_mv()*100)/4200;
}

uint16_t _get_battery_value(void)
{
    return (uint16_t) adc1_get_raw(BATTERY_PIN);
}
    