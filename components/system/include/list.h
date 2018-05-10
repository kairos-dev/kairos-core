#ifndef LIST_H
#define LIST_H

#define LIST_INIT_CAPACITY 4

#define LIST_INIT(list) list_t list; list_init(&list)
#define LIST_ADD(list, item) list_append(&list, (void *) item)
#define LIST_SET(list, id, item) list_set(&list, id, (void *) item)
#define LIST_GET(list, type, id) (type) list_get(&list, id)
#define LIST_DELETE(list, id) list_delete(&list, id)
#define LIST_POP(list) list_pop(&list)
#define LIST_LENGTH(list) list_length(&list)
#define LIST_FREE(list) list_free(&list)
#define LIST_INSERT(list, id, item) list_insert(&list, id, (void *) item)

typedef struct vector {
    void **items;
    int capacity;
    int total;
} list_t;

void list_init(list_t *);
int  list_length(list_t *);
void list_resize(list_t *, int);
void list_append(list_t *, void *);
void list_insert(list_t *, int, void *);
void list_set(list_t *, int, void *);
void *list_get(list_t *, int);
void list_delete(list_t *, int);
void list_free(list_t *);
void list_pop(list_t *);

#endif