#include <stdlib.h>
#include <system.h>
#include <linked_list.h>

void linked_list_init(linked_list_t **list){
    (*list) = NULL;
}

kairos_err_t linked_list_is_empty(linked_list_t **list){
    if((*list)->next==NULL)    return KAIROS_ERR_OK;
    else                    return KAIROS_ERR_FAIL;
}

kairos_err_t linked_list_append(linked_list_t **list, void *data){
    linked_list_t *new = (linked_list_t*)malloc(sizeof(linked_list_t));
    if(new == NULL)     return KAIROS_ERR_FAIL;
    new->data = data;
    new->next = *list;
    *list = new;
    return KAIROS_ERR_OK;
}

kairos_err_t linked_list_insert(linked_list_t **list, void *data){
    linked_list_t *new = NULL, *actual = NULL;
    new = (linked_list_t*)malloc(sizeof(linked_list_t));
    if(new == NULL)     return KAIROS_ERR_FAIL;
    new->data = data;
    new->next = NULL;

    if(*list == NULL)   *list = new;
    else{
        actual = *list;
        while(actual->next != NULL){
            actual = actual->next;
        }
        actual->next = new;
    }
    return KAIROS_ERR_OK;
}
kairos_err_t linked_list_pop(linked_list_t **list){
    if(*list == NULL)   return KAIROS_ERR_FAIL;
    else{
        linked_list_t *actual;
        actual = *list;
        *list = (*list)->next;
        free(actual);
    }
    return KAIROS_ERR_OK;
}
kairos_err_t linked_list_remove(linked_list_t **list){
    if(*list == NULL)   return KAIROS_ERR_FAIL;
    else{
        linked_list_t *actual = NULL, *previous = NULL;
        actual = *list;
        while(actual->next != NULL){
            previous = actual;
            actual = actual->next;
        }
        previous->next = NULL;
        free(actual);
    }
    return KAIROS_ERR_OK;
}
