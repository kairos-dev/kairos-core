#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <test_list.h>
#include <app.h>

void bluetooth_test(void){
	printf("This is a false test including bluetooth!\n");
}

void app_main(void){

	app_t test = {
		.name = "Test",
		.company = "Kairos",
		.bluetooth = &bluetooth_test
	};

	if(test.bluetooth != NULL){
		test.bluetooth();
		printf("App Name: %s\n", test.name);
		printf("Company: %s\n", test.company);
	}
	if(test.on_init != NULL)	test.on_init();
	else printf("on_init() doesn't exist!\n");


    test_list();
}
