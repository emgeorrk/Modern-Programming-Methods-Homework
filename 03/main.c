#include <stdio.h>
#include <malloc.h>

typedef struct _Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct _LinkedList {
    size_t size;
    Node *head;
    Node *tail;
} LinkedList;

LinkedList *create() {
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp -> size = 0;
    temp -> head = NULL;
    temp -> tail = NULL;
    return temp;
}

void push_back(void *data, LinkedList *list) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp -> value = data;
    temp -> next = NULL;
    temp -> prev = list -> tail;
    if (list -> tail) list -> tail -> next = temp;
    list -> tail = temp;
    if (list -> head == NULL) list -> head = temp;
    list -> size++;
}

void push_front(void *data, LinkedList *list) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp -> value = data;
    temp -> next = list -> head;
    temp -> prev = NULL;
    if (list -> head) list -> head -> prev = temp;
    list -> head = temp;
    if (list -> tail == NULL) list -> tail = temp;
    list -> size++;
}

void* pop_back(LinkedList *list) {
    Node *next;
    void *temp;
    if (list -> tail == NULL) return NULL;
    next = list -> tail;
    list -> tail = list -> tail -> prev;
    if (list -> tail) list -> tail -> next = NULL;
    if (next == list -> head) list -> head = NULL;
    temp = next -> value;
    free(next);
    list -> size--;
    return temp;
}

void* pop_front(LinkedList *list) {
    Node *prev;
    void *temp;
    if (list -> head == NULL) return NULL;
    prev = list -> head;
    list -> head = list -> head -> next;
    if (list -> head) list -> head -> prev = NULL;
    if (prev == list -> tail) list -> tail = NULL;
    temp = prev -> value;
    free(prev);
    list -> size--;
    return temp;
}

Node* get_n(size_t index, LinkedList *list) {
    Node *temp = list -> head;
    size_t i = 0;
    while (temp && i < index) {
        temp = temp -> next;
        i++;
    }
    return temp;
}

void push_n(void *data, size_t index, LinkedList *list) {
    Node *elm = NULL;
    elm = get_n(index, list);
    if (elm == NULL) return;
    Node *ins = (Node*)malloc(sizeof(Node));
    ins -> value = data;
    ins -> prev = elm;
    ins -> next = elm -> next;
    if (elm -> next) {
        Node *nxt = elm -> next;
        nxt -> prev = ins;
    }
    elm -> next = ins;
    if (!elm -> prev) list -> head = elm; //
    if (!elm -> next) list -> tail = elm; //
    list -> size++;
}

void* pop_n(size_t index, LinkedList *list) {
    Node *elm = NULL;
    void *temp = NULL;
    elm = get_n(index, list);
    if (elm == NULL) return NULL;
    if (elm -> prev) {
        Node *prv = elm -> prev;
        prv -> next = elm -> next;
    }
    if (elm -> next){
        Node *nxt = elm -> next;
        nxt -> prev = elm -> prev;
    }
    temp = elm -> value;
    if (!elm -> prev) list -> head = elm -> next;
    if (!elm -> next) list -> tail = elm -> prev;
    free(elm);
    list -> size--;
    return temp;
}

void remove_all(LinkedList *list) {
    Node *temp = list -> head;
    Node *next = NULL;
    while (temp != NULL) {
        next = temp -> next;
        free(temp);
        temp = next;
    }
    list -> size = 0;
    list -> head = NULL;
    list -> tail = NULL;
}

void print_elements(LinkedList *list) {
    Node *temp = list -> head;
    while (temp) {
        printf("%d ", temp -> value);
        temp = temp -> next;
    }
    printf("\n");
}

int main() {
    LinkedList *a = create();
    push_back(2, a);
    push_back(4, a);
    print_elements(a);
    push_front(1, a);
    print_elements(a);
    push_n(3, 1, a);
    push_n(9, 0, a);
    print_elements(a);
    pop_n(1, a);
    print_elements(a);
    pop_front(a);
    pop_back(a);
    print_elements(a);
    printf("%d\n", get_n(0, a) -> value);
    push_back(7, a);
    push_front(4, a);
    print_elements(a);
    remove_all(a);
    push_back(5, a);
    print_elements(a);
}

/*
    OUTPUT:
    2 4
    1 2 4
    1 9 2 3 4
    1 2 3 4
    2 3
    2
    4 2 3 7
    5

    Process finished with exit code 0
*/