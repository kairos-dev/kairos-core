#ifndef _APPMANAGER_H_
#define _APPMANAGER_H_

#include<stdlib.h>
#include<app.h>
#include <circular_linked_list.h>
#include<system.h>

typedef circ_list_t app_manifest_t;

app_manifest_t *app_manifest;

void appmanager_app_loader_init();

void appmanager_add_to_manifest(app_t *app);

app_t *appmanager_get_manifest();

app_t *appmanager_get_app_by_name(char *appname);

app_t *appmanager_get_app_by_id(unsigned int appid);

#endif