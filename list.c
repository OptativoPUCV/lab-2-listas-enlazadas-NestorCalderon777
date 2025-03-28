#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* newlista = malloc(sizeof(List));
    newlista->head = NULL;
    newlista->tail = NULL;
    newlista->current = NULL;
    
    return newlista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;

    return list->current->data;
}

void * nextList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    
    list->current = list->current->next;

    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);

    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    } else{
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->prev = list->current;
    newNode->next = list->current->next;

    if(list->current->next != NULL){
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    list->current->next = newNode;

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL) return NULL;
    Node *remove = list->current;
    void *elem = remove->data;

    if(list->head == remove && list->tail == remove){
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    }

    else if(list->head == remove){
        list->head = remove->next;
        list->head->prev = NULL;
        list->current = list->head;
    }

    else if(list->tail == remove){
        list->tail = remove->prev;
        list->tail->next = NULL;
        list->current = NULL;
    }

    else{
        remove->prev->next = remove->next;
        remove->next->prev = remove->prev;
        list->current = remove->next;
    }

    free(remove);
    return elem;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}