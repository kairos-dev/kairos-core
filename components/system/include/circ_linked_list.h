#ifndef _CIRC_LINKED_LIST_H_
#define _CIRC_LINKED_LIST_H_

struct Node{
    void *data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node circ_linked_list_t;

circ_linked_list_t* new_node(void *data);

void CLL_insert_begin(circ_linked_list_t **head, void *data);

void CLL_insert_end(circ_linked_list_t **head, void *data);

void* CLL_get_next(circ_linked_list_t **head);

void* CLL_get_previous(circ_linked_list_t **head);

void* CLL_get_actual(circ_linked_list_t **head);


// void linked_list_init(linked_list_t **list);
// kairos_err_t linked_list_is_empty(linked_list_t **list);
// kairos_err_t linked_list_append(linked_list_t **list, void *data);
// kairos_err_t linked_list_insert(linked_list_t **list, void *data);
// kairos_err_t linked_list_pop(linked_list_t **list);
// kairos_err_t linked_list_remove(linked_list_t **list);

#endif