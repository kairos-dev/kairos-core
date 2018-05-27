#include <stdio.h>
#include <stdlib.h>
#include <dynamic_list.h>
#include <appmanager.h>
#include <app.h>
#include <system.h>
#include <menu.h>
#include <linked_list.h>
#include <circ_linked_list.h>

void bluetooth_test1(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth1 - %s!\n", app->name);
}

void bluetooth_test2(void *aux){
	app_t *app = (app_t*)aux;
	printf("This is a false test including bluetooth2 - %s!\n", app->name);
}

void _on_init(void *aux){
	app_t *app = (app_t*)aux;
	printf("%s - on_init()\n", app->name);
}

void _on_close(void *aux){
	app_t *app = (app_t*)aux;
	printf("%s - on_close()\n", app->name);
}

void test_apps(void){
	appmanager_add_to_manifest(app_create("Test 1", (appversion_t){.release = 1, .func_added = 0, .bug_fixed=3}, _on_init, _on_close));
	appmanager_add_to_manifest(app_create("Test 2", (appversion_t){.release = 2, .func_added = 0, .bug_fixed=4}, _on_init, _on_close));
	appmanager_add_to_manifest(app_create("Test 3", (appversion_t){.release = 3, .func_added = 1, .bug_fixed=5}, _on_init, _on_close));
	appmanager_add_to_manifest(app_create("Test 4", (appversion_t){.release = 4, .func_added = 2, .bug_fixed=6}, _on_init, _on_close));

	app_t *manifest = appmanager_get_manifest();
	if(manifest == NULL) printf("Manifest não existe!\n");
	while(manifest){
		(*manifest).on_init(manifest);
		(*manifest).on_close(manifest);
		manifest = manifest->next;
	}
}

void print_sth(circ_linked_list_t *node){
    printf("%d\t", (int)node->data);
    node = node->next;
    printf("%d\t", (int)node->data);
    node = node->prev;
    printf("%d\t", (int)node->data);
}

void app_main(void){
	list_t main_menu;
	list_init(&main_menu);
	list_append(&main_menu, app_create("Test 1", (appversion_t){.release = 1, .func_added = 0, .bug_fixed=3}, _on_init, _on_close));
	list_append(&main_menu, app_create("Test 2", (appversion_t){.release = 2, .func_added = 0, .bug_fixed=4}, _on_init, _on_close));
	for(unsigned int index = 0; index < list_length(&main_menu); index++){
		app_t *aux = LIST_GET(main_menu, app_t*, index);
		(*aux).on_init(aux);
	}

	linked_list_t *main_list = NULL;
	
	linked_list_init(&main_list);
	linked_list_insert(&main_list, app_create("Test 3", (appversion_t){.release = 1, .func_added = 0, .bug_fixed=3}, _on_init, _on_close));
	linked_list_insert(&main_list, app_create("Test 4", (appversion_t){.release = 2, .func_added = 0, .bug_fixed=4}, _on_init, _on_close));
	
	linked_list_t *temp = main_list;
	if(temp == NULL)	printf("\nLista Vazia!\n");
	while(temp != NULL){
		app_t *aux = (app_t*)temp->data;
		(*aux).on_init(aux);
        temp = temp->next;         
    }

	circ_linked_list_t *head = NULL;
	
	CLL_insert_begin(&head, (void*)1); Print(&head); ReversePrint(&head);
	CLL_insert_begin(&head, (void*)7); Print(&head); ReversePrint(&head);
	CLL_insert_end(&head, (void*)9); Print(&head); ReversePrint(&head);
	Print(&head);
	printf("Actual: %d\n", (int)head->data);
	printf("GET_NEXT(): %d\n", (int)CLL_get_next(&head));
	printf("GET_NEXT(): %d\n", (int)CLL_get_next(&head));
	printf("GET_NEXT(): %d\n", (int)CLL_get_next(&head));
	printf("Actual: %d\n", (int)head->data);
	printf("GET_PREVIOUS(): %d\n", (int)CLL_get_previous(&head));
	printf("GET_PREVIOUS(): %d\n", (int)CLL_get_previous(&head));
}
