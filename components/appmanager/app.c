#include <system.h>
#include <app.h>
#include <stdlib.h>
#include <string.h>



app_info_t create_app_info(char *app_name, char *plain_text, char *company_name)
{
	app_info_t aux_info;
	strncpy(aux_info.name, app_name, APP_NAME_BYTES);
	strncpy(aux_info.plain_text, plain_text, APP_NAME_BYTES);
	strncpy(aux_info.company, company_name, APP_NAME_BYTES);
	return aux_info;
}

app_version_t create_app_version(uint8_t major, uint8_t minor, uint8_t patch)
{
	return (app_version_t){.major = major, .minor = minor, .patch = patch};
}

app_functions_t create_app_functions(void (*bluetooth)(void), void (*gyro)(void), void (*pulse_oximeter)(void), void (*heart_rate)(void))
{
	return (app_functions_t){.bluetooth = bluetooth, .gyro = gyro, .pulse_oximeter = pulse_oximeter, .heart_rate = heart_rate};
}

app_t *app_create(app_info_t app_info, app_version_t app_version, app_functions_t app_functions, icon_t app_icon, void *on_init, void *on_close)
{
	app_t *aux_app = calloc(1, sizeof(app_t));
	(*aux_app).info = app_info;
	(*aux_app).version = app_version;
	(*aux_app).functions = app_functions;
	(*aux_app).icon = app_icon;
	(*aux_app).on_init = on_init;
	(*aux_app).on_close = on_close;
	// strncpy((*aux_app).name, appname, APP_NAME_BYTES);
	// (*aux_app).app_version = app_version;
	// (*aux_app).on_init = on_init;
	// (*aux_app).on_close = on_close;
	return aux_app;
}

kairos_err_t app_set_functions(app_t *app, app_functions_t functions){
	kairos_err_t error = 0;
	if(app != NULL){
		app->functions = functions;
		error = KAIROS_ERR_OK;
	}else error = KAIROS_ERR_FAIL;
	return error;
}

kairos_err_t app_get_functions(app_t *app, app_functions_t *functions){
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
