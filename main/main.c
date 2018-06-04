#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dynamic_list.h>
#include <appmanager.h>
#include <app.h>
#include <system.h>
#include <menu.h>
#include <linked_list.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <u8g2_esp32_hal.h>
#include <display.h>
#include <top_menu_icons.h>
#include <app_icons.h>

#define BUTTON_NEXT    		 GPIO_NUM_4
#define BUTTON_SELECT		 GPIO_NUM_5
#define BUTTON_PREVIOUS      GPIO_NUM_15

void bluetooth_test1(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth1 - %s!\n", (*app).info.name);
}

void bluetooth_test2(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth2 - %s!\n", (*app).info.name);
}

void _on_init(void *aux){
	app_t *app = (app_t*)aux;
	printf("%s - on_init()\n", (*app).info.name);
}

void _on_close(void *aux){
	app_t *app = (app_t*)aux;
	printf("%s - on_close()\n", (*app).info.name);
}

void test_apps(void){
	app_info_t aux_info;
	app_version_t aux_version;
	app_functions_t aux_functions;
	icon_t aux_icon = notification_icon;
	aux_info = create_app_info("Notifications", "Notifications", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	aux_icon = configuration_icon;
	aux_info = create_app_info("Configurations", "Configurations", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	aux_icon = heart_rate_icon;
	aux_info = create_app_info("Heart Rate", "Heart Rate", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	aux_icon = spo2_icon;
	aux_info = create_app_info("SPO2", "SPO2", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	aux_icon = steps_icon;
	aux_info = create_app_info("Steps", "Steps", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	aux_icon = calories_icon;
	aux_info = create_app_info("Calories", "Calories", "Kairos-dev");
	aux_version = create_app_version(0, 0, 0);
	aux_functions = create_app_functions(NULL, NULL, NULL, NULL);
	appmanager_add_to_manifest(app_create(aux_info, aux_version, aux_functions, aux_icon, _on_init, _on_close));

	main_menu = create_main_menu(app_manifest);
}

void app_main(void){
    gpio_pad_select_gpio(BUTTON_NEXT);
    gpio_set_direction(BUTTON_NEXT, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(BUTTON_SELECT);
    gpio_set_direction(BUTTON_SELECT, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(BUTTON_PREVIOUS);
    gpio_set_direction(BUTTON_PREVIOUS, GPIO_MODE_INPUT);

	test_apps();
	u8g2_t display = display_setup();
	u8g2_ClearBuffer(&display);
	display_battery(display, battery_charging);
	display_bluetooth(display, bluetooth_bits);
	display_icon(display, notification_icon);
	display_text(display, "Notifications");
	u8g2_SendBuffer(&display);
	app_t *aux = (app_t*)menu_get_selected(main_menu);

	while(1)
	{	
        if(gpio_get_level(BUTTON_NEXT) && !gpio_get_level(BUTTON_PREVIOUS))
		{
			while(gpio_get_level(BUTTON_NEXT) && !gpio_get_level(BUTTON_PREVIOUS));
			display_animate_right_arrow(display, battery_charging, bluetooth_bits, *aux);
			aux = (app_t*)menu_next_item(main_menu);
			printf("%s\n", (*aux).info.name);
			display_screen(display, battery_charging, bluetooth_bits, *aux);
		}
		else if(!gpio_get_level(BUTTON_NEXT) && gpio_get_level(BUTTON_PREVIOUS))
		{	
			while(!gpio_get_level(BUTTON_NEXT) && gpio_get_level(BUTTON_PREVIOUS));
			display_animate_left_arrow(display, battery_charging, bluetooth_bits, *aux);
			aux = (app_t*)menu_previous_item(main_menu);
			printf("%s\n", aux->info.name);
			display_screen(display, battery_charging, bluetooth_bits, *aux);
		}
		else if(gpio_get_level(BUTTON_SELECT))
		{
			while(gpio_get_level(BUTTON_SELECT));
			aux = (app_t*)menu_get_selected(main_menu);
			(*aux).on_init(aux);
		}
		vTaskDelay(10);
	}
}
