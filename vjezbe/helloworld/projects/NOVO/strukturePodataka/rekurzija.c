// Recursive C program to reverse a linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Given the head of a list, reverse the list and return the
// head of reversed list
struct Node* reverseList(struct Node* head) {
    if (head == NULL || head->next == NULL)
        return head;


    // reverse the rest of linked list and put the first element at the end
    struct Node* rest = reverseList(head->next);
    printf("\nHead: %d\n",head->data);

    // Make the current head as last node of remaining linked list
    head->next->next = head;

    // Update next of current head to NULL
    head->next = NULL;

    // Return the reversed linked list
    return rest;
}


// This function prints the contents
// of the linked list starting from the head
void printList(struct Node* node) {
    while (node != NULL) {
        printf(" %d", node->data);
        node = node->next;
    }
    printf("\n");
}

struct Node* createNode(int new_data) {
    struct Node* new_node = 
       (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {
  
    // Create a hard-coded linked list:
    // 1 -> 2 -> 3 -> 4 -> 5
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Given Linked List:");
    printList(head);

    head = reverseList(head);

    printf("Reversed Linked List:");
    printList(head);

    return 0;
}
