#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <app.h>

struct menuitem_t{
	char text[APP_NAME_BYTES];
	char sub_stext[APP_NAME_BYTES];
	app_t app;
	uint16_t image_logo;
};

typedef struct menuitem_t menuitem_t;

#endif