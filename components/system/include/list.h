#ifndef LIST_H
#define LIST_H

#define LIST_INIT_CAPACITY 4

#define LIST_INIT(list) list_t list; list_init(&list)
#define LIST_ADD(list, item) list_add(&list, (void *) item)
#define LIST_SET(list, id, item) list_set(&list, id, (void *) item)
#define LIST_GET(list, type, id) (type) list_get(&list, id)
#define LIST_DELETE(list, id) list_delete(&list, id)
#define LIST_TOTAL(list) list_total(&list)
#define LIST_FREE(list) list_free(&list)

typedef struct vector {
    void **items;
    int capacity;
    int total;
} list_t;

void list_init(list_t *);
int list_total(list_t *);
// static void list_resize(list_t *, int);
void list_resize(list_t *, int);
void list_add(list_t *, void *);
void list_set(list_t *, int, void *);
void *list_get(list_t *, int);
void list_delete(list_t *, int);
void list_free(list_t *);

#endif