#include <menu.h>

menu_t* create_main_menu(app_manifest_t *manifest)
{
    return (menu_t*)manifest;
}

void* menu_next_item(menu_t *menu)
{
    node_t *aux = cll_get_next(menu);
    return aux->element;
}

void* menu_previous_item(menu_t *menu)
{
    node_t *aux = cll_get_previous(menu);
    return aux->element;
}

void* menu_get_selected(menu_t *menu){
    return cll_get_actual(menu);
}