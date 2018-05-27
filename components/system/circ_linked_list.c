#include <stdio.h>
#include <stdlib.h>
#include <circ_linked_list.h>

//Creates a new Node and returns pointer to it. 
circ_linked_list_t* new_node(void *data) {
	circ_linked_list_t* newNode = (circ_linked_list_t*)malloc(sizeof(circ_linked_list_t));
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void CLL_insert_begin(circ_linked_list_t **head, void *data) {
	circ_linked_list_t* newNode = new_node(data);
	if(*head == NULL) {
		(*head) = newNode;
		return;
	}
	(*head)->prev = newNode;
	newNode->next = (*head); 
	(*head) = newNode;
}

//Inserts a Node at tail of Doubly linked list
void CLL_insert_end(circ_linked_list_t **head, void *data) {
	circ_linked_list_t* temp = (*head);
	circ_linked_list_t* newNode = new_node(data);
	if((*head) == NULL) {
		(*head) = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

void* CLL_get_next(circ_linked_list_t **head){
    circ_linked_list_t *temp = (*head);
    if((*head)->next == NULL) return (NULL);
    (*head) = (*head)->next;
    (*head)->prev = temp;
    return (*head)->data;
}

void* CLL_get_previous(circ_linked_list_t **head){
    circ_linked_list_t *temp = (*head);
    if((*head)->prev == NULL) return NULL;
    (*head) = (*head)->prev;
    (*head)->prev = temp;
    return (*head)->data;
}

void* CLL_get_actual(circ_linked_list_t **head){
    if((*head) == NULL) return NULL;
    return (*head)->data;
}

//Prints all the elements in linked list in forward traversal order
void Print(circ_linked_list_t **head) {
	circ_linked_list_t* temp = (*head);
	printf("Forward: ");
	while(temp != NULL) {
		printf("%d ",(int)temp->data);
		temp = temp->next;
	}
	printf("\n");
}

//Prints all elements in linked list in reverse traversal order. 
void ReversePrint(circ_linked_list_t **head) {
	circ_linked_list_t* temp = (*head);
	if(temp == NULL) return; // empty list, exit
	// Going to last Node
	while(temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	printf("Reverse: ");
	while(temp != NULL) {
		printf("%d ",(int)temp->data);
		temp = temp->prev;
	}
	printf("\n");
}