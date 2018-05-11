#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <appmanager.h>
#include <app.h>
#include <system.h>

void bluetooth_test1(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth1 - %s!\n", app->name);
}

void bluetooth_test2(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth2 - %s!\n", app->name);
}

void app_main(void){

	app_t test1;
	test1 = app_create("Test 1", (appversion_t){.release = 1, .func_added = 0, .bug_fixed=3}, bluetooth_test1, bluetooth_test2);
	appmanager_add_to_manifest(&test1);

	app_t *test = appmanager_get_app_by_name("Test 1");

	(*test).on_init(test);
	(*test).on_close(test);
}
