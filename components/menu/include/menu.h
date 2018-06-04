#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <app.h>
#include <appmanager.h>
#include <circular_linked_list.h>

typedef circ_list_t menu_t;

menu_t* main_menu, *app_menu, *sub_menu;

menu_t* create_main_menu(app_manifest_t *manifest);

void* menu_next_item(menu_t *menu);

void* menu_previous_item(menu_t *menu);

void* menu_get_selected(menu_t *menu);

#endif