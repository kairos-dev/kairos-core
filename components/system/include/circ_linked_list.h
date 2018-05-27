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

void Print(circ_linked_list_t **head) ;

void ReversePrint(circ_linked_list_t **head) ;

#endif