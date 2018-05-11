#ifndef APPMANAGER_H
#define APPMANAGER_H

#include<app.h>
#include<system.h>
#include<stdlib.h>

typedef list_t app_manifest_t;

app_t *app_manifest_head;

void appmanager_app_loader_init();

void appmanager_add_to_manifest(app_t *app);

app_t *appmanager_get_manifest();

app_t *appmanager_get_app_by_name(char *appname);

app_t *appmanager_get_app_by_id(unsigned int appid);

#endif