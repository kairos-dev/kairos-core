#include <string.h>
#include <circular_linked_list.h>
#include <app.h>
#include <appmanager.h>

void appmanager_add_to_manifest(app_t *app){
	if(app_manifest == NULL){
		app_manifest = cll_create();
	}
	cll_push_back(app_manifest, app);
}

// app_t *appmanager_get_app_by_name(char *appname){
// 	app_t *aux;
// 	if(cll_is_empty(app_manifest))
// 	{
// 		return NULL;
// 	}
// 	cll_goto_head(app_manifest);
// 	size_t size_of_manifest = cll_get_size(app_manifest);
// 	for(unsigned int index = 0; index < size_of_manifest; index++)
// 	{
// 		aux = (app_t*)cll_get_actual(app_manifest);
// 		if(!strncmp(aux->name, (char*)appname, strlen(aux->name)))
// 		{
// 			return (app_t*)aux;
// 		}
// 	}
//     return NULL;
// }

app_t *appmanager_get_manifest(void){
	return (app_t*)app_manifest;
}

