#ifndef APP_H
#define APP_H 
#include <stdint.h>
#include <system.h>

#define APP_NAME_BYTES			30
#define COMPANY_NAME_BYTES 		30

typedef struct {
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
}app_version_t;

typedef struct 
{
    uint8_t widht;
    uint8_t heidht;
    const uint8_t *image;
}icon_t;
typedef struct {
    void (*bluetooth)(void);
    void (*gyro)(void);
    void (*pulse_oximeter)(void);
    void (*heart_rate)(void);
}app_functions_t;

typedef struct
{
	char name[APP_NAME_BYTES];
	char plain_text[APP_NAME_BYTES];
	char company[APP_NAME_BYTES];
}app_info_t;
typedef struct 
{                 
	app_info_t info;
	app_version_t version;	
 	app_functions_t functions;
 	icon_t icon;
 	void (*on_init)(void*);
    void (*on_close)(void*);
}app_t;

app_t *app_create(app_info_t app_info, app_version_t app_version, app_functions_t app_functions, icon_t app_icon, void *on_init, void *on_close);

app_info_t create_app_info(char *app_name, char *plain_text, char *company_name);

app_version_t create_app_version(uint8_t major, uint8_t minor, uint8_t patch);

app_functions_t create_app_functions(void (*bluetooth)(void), void (*gyro)(void), void (*pulse_oximeter)(void), void (*heart_rate)(void));

kairos_err_t app_set_functions(app_t *app, app_functions_t functions);

kairos_err_t app_get_functions(app_t *app, app_functions_t *functions);

kairos_err_t app_close(app_t *app);

#endif