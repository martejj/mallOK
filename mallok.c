#define MALLOK_MACROS
#include "mallok.h"
#include <stdio.h>
#define MALLOK_DEBUG 0

typedef struct node *Node;

struct node {
    size_t size;
    int line;
    char *file;
    void *ptr;
    Node next;
};

Node head = NULL;
Node tail = NULL;

static Node newNode(size_t size, char * file, int line, void *ptr);

void *mallokMalloc(size_t size, char *file, int line) {

    void *ptr = malloc(size);
        
    if (ptr == NULL) {
        return NULL;
    }
    
    #if MALLOK_DEBUG
    printf("%s:%d allocated %ld bytes\n", file, line, size);
    #endif 
    
    Node new = newNode(size, file, line, ptr);
    
    if (head == NULL) {
        head = new;
        tail = new;
        return ptr;
    }
    
    tail->next = new;
    
    return ptr;
    
}

void mallokFree(void *ptr) {
    
    if (ptr == NULL) {
        return;
    }
    
    if (head == NULL) {
        printf("Nothing allocated?\n");
    }
    
    if (head->ptr == ptr) {
        #if MALLOK_DEBUG
        printf("%s:%d %ld bytes were freed\n", head->file, head->line, head->size);
        #endif 
        free(head);
        head = NULL;
        tail = NULL;
        return;
    }
    
    Node curr = head;
    
    while(curr->next != NULL && curr->next->ptr != ptr) {
        curr = curr->next;
    }
    
    // 2 cases: curr->next = NULL. curr->next->ptr == ptr
    
    if (curr->next == NULL) {
        printf("Couldnt find memory\n");
    }
    
    Node temp = curr->next;
    curr->next = curr->next->next;
    #if MALLOK_DEBUG
    printf("%s:%d %ld bytes were freed\n", temp->file, temp->line, temp->size);
    #endif 
    free(temp);
    
    free(ptr);
}

void mallok() {
    Node curr = head;
    while (curr != NULL) {
        printf("%s:%d %ld bytes not freed\n", curr->file, curr->line, curr->size);
        curr = curr->next;
    }
}

static Node newNode(size_t size, char * file, int line, void *ptr) {

    Node new = malloc(sizeof(*new));
    new->size = size;
    new->file = file;
    new->line = line;
    new->ptr = ptr;
    new->next = NULL;
    return new;
    
}