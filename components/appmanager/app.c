#include <system.h>
#include <app.h>
#include <stdlib.h>
#include <string.h>

app_t app_create(char *appname, appversion_t app_version, void *on_init, void *on_close){
	app_t aux_app;
	strncpy(aux_app.name, appname, APP_NAME_BYTES);
	aux_app.app_version = app_version;
	aux_app.on_init = on_init;
	aux_app.on_close = on_close;
	return aux_app;
}

kairos_err_t app_set_functions(app_t *app, app_functions functions){
	kairos_err_t error = 0;
	if(app != NULL){
		app->functions = functions;
		error = KAIROS_ERR_OK;
	}else error = KAIROS_ERR_FAIL;
	return error;
}

kairos_err_t app_get_functions(app_t *app, app_functions *functions){
	kairos_err_t error = 0;
	if(app != NULL){
		*functions = app->functions;
		error = KAIROS_ERR_OK;
	}else error = KAIROS_ERR_FAIL;
	return error;
}

kairos_err_t app_close(app_t *app){
	kairos_err_t error = 0;
	if(app != NULL){
		app = NULL;
		error = KAIROS_ERR_OK;
	}else error = KAIROS_ERR_FAIL;
	return error;
}