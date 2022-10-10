#include <stdio.h>
#include <malloc.h>

struct Node {
    int value;
    struct Node *next;
};

typedef struct Node LinkedList;

LinkedList *create(int data) {
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp -> value = data;
    temp -> next = NULL;
    return(temp);
}

void add(int data, int n, LinkedList *head) {
    if (n == 0) return;
    LinkedList *p = head;
    int count = 1;
    while (count < n - 1) {
        p = p -> next;
        if (p -> next == NULL) return;
        count++;
    }
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp -> value = data;
    temp -> next = (n == 0) ? head : p -> next;
    p -> next = temp;
}

int SizeOfList(LinkedList *head) {
    int count = 1;
    LinkedList *p = head;
    while (p -> next != NULL) {
        p = p -> next;
        count++;
    }
    return count;
}

void push_back(int data, LinkedList *head) {
    LinkedList *p = head;
    while (p -> next != NULL) p = p -> next;
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp -> value = data;
    temp -> next = NULL;
    p -> next = temp;
}

LinkedList *push_front(int data, LinkedList *head) {
    LinkedList *temp = (LinkedList*)malloc(sizeof(LinkedList));
    temp -> value = data;
    temp -> next = head;
    return temp;
}

void remove_element(int data, LinkedList *head) {
    LinkedList *temp = head, *p = NULL;
    if (head == NULL) return NULL;
    while (temp && temp -> value != data) {
        p = temp;
        temp = temp -> next;
    }
    if (temp == head) {
        free(head);
        return temp -> next;
    }
    if (!temp) return head;
    p -> next = temp -> next;
    free(temp);
}

void remove_all(LinkedList *head) {
    while (head != NULL) {
        LinkedList *p = head;
        head = head -> next;
        free(p);
    }
}

void print_elements(LinkedList *head) {
    LinkedList *p = head;
    while (p != NULL) {
        printf("%d ", p -> value);
        p = p -> next;
    }
    printf("\n");
}

int main() {
    LinkedList *a = create(1);
    print_elements(a);
    push_back(2, a);
    print_elements(a);
    remove_element(2, a);
    print_elements(a);
    add(8, 2, a);
    print_elements(a);
    add(3, 2, a);
    print_elements(a);
    push_back(91, a);
    print_elements(a);
    a = push_front(118, a);
    print_elements(a);
    remove_all(a);
    print_elements(a);
}

/*
    OUTPUT:
    1
    1 2
    1
    1 8
    1 3 8
    1 3 8 91
    118 1 3 8 91
*/
