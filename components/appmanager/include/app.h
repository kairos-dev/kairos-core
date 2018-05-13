#ifndef APP_H
#define APP_H 
#include <stdint.h>
#include <system.h>

#define APP_NAME_BYTES			30
#define COMPANY_NAME_BYTES 		30

typedef struct {
	uint8_t release;
	uint8_t func_added;
	uint8_t bug_fixed;
}appversion_t;

typedef struct {
    void (*bluetooth)(void);
    void (*gyro)(void);
    void (*pulse_oximeter)(void);
    void (*heart_rate)(void);
}app_functions;

struct app_t{
	appversion_t app_version;	                 
 	char name[APP_NAME_BYTES];        	 
 	char company[COMPANY_NAME_BYTES]; 	 
 	uint32_t icon_resource_id;
 	void (*on_init)(void*);
    void (*on_close)(void*);
 	app_functions functions;
 	struct app_t *next;
};

typedef struct app_t app_t;

app_t *app_create(char *appname, appversion_t app_version, void *on_init, void *on_close);

kairos_err_t app_set_functions(app_t *app, app_functions functions);

kairos_err_t app_get_functions(app_t *app, app_functions *functions);

kairos_err_t app_close(app_t *app);

#endif