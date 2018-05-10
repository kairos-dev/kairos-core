#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <test_list.h>

void test_list(void){
	int i;

    LIST_INIT(v);

    LIST_ADD(v, 1);
    LIST_ADD(v, 2);
    LIST_ADD(v, 3);
    LIST_ADD(v, 4);
    LIST_ADD(v, 2);
    LIST_ADD(v, 1);

    for (i = 0; i < LIST_TOTAL(v); i++)
        printf("%d ", LIST_GET(v, int, i));
    printf("\n");

    LIST_DELETE(v, 0);
    LIST_DELETE(v, 1);

    for (i = 0; i < LIST_TOTAL(v); i++)
        printf("%d ", LIST_GET(v, int, i));
    printf("\n");

	list_t lista;
    list_init(&lista);

    list_add(&lista, "Bom dia");
    list_add(&lista, "todo");
    list_add(&lista, "o");
    list_add(&lista, "Mundo");

    for (i = 0; i < list_total(&lista); i++)
        printf("%s ", (char *) list_get(&lista, i));
    printf("\n");

    LIST_INIT(value);

    data_t aux_data1 = {
    	.data = 10
    };
    LIST_ADD(value, &aux_data1);

    data_t aux_data2 = {
    	.data = 15
    };
    LIST_ADD(value, &aux_data2);

    data_t aux_data3 = {
    	.data = 20
    };
    LIST_ADD(value, &aux_data3);


    data_t *aux;
    for (i = 0; i < LIST_TOTAL(value); i++){
    	aux = LIST_GET(value, data_t*, i);
    	printf("%d\n", aux->data);
    }
    list_free(&lista);
    LIST_FREE(v);
    LIST_FREE(value);
}