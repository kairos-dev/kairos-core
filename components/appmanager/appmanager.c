#include <appmanager.h>
#include <string.h>
void appmanager_add_to_manifest(app_t *app){
	// DYNAMIC ARRAY
	// if(app_manifest_head == NULL){
	// 	list_init(app_manifest_head);
	// }
	// list_append(app_manifest_head, app);	
	// LINKED LIST
	if(app_manifest_head == NULL){
		app_manifest_head = app;
	}else{
		app_t *child = app_manifest_head;
		while(child->next)	child = child->next;
    	child->next = app;
	}
}

app_t *appmanager_get_app_by_name(char *appname){
	app_t *node = app_manifest_head;
	while(node){
		if (!strncmp(node->name, (char *)appname, strlen(node->name)))	return node;
		node = node->next;
	}
    return NULL;
}

app_t *appmanager_get_manifest(void){
	return app_manifest_head;
}

