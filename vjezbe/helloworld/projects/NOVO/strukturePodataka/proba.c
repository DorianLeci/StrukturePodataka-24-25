// C program to remove duplicates from an 
// unsorted linked list

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to remove duplicates using nested loops
struct Node* removeDuplicates(struct Node* head) {
    struct Node* curr1 = head; 

    // Traverse each node in the list
    while (curr1 != NULL) {
        struct Node* curr2 = curr1; 

        // Traverse the remaining nodes to find and 
        // remove duplicates
        while (curr2->next != NULL) {
            
            // Check if the next node has the same 
            // data as the current node
            if (curr2->next->data == curr1->data) {
                
                // Duplicate found, remove it
                struct Node* duplicate = curr2->next;  
                curr2->next = curr2->next->next;  

                // Free the memory of the duplicate node
                free(duplicate);
            } else {
              
                // If the next node has different data from 
                // the current node, move to the next node
                curr2 = curr2->next;
            }
        }
        
        // Move to the next node in the list
        curr1 = curr1->next;
    }
    return head;
}

void printList(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct Node* createNode(int data) {
    struct Node* newNode =
      (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    // Create a singly linked list:
    // 12 -> 11 -> 12 -> 21 -> 41 -> 43 -> 21
    struct Node* head = createNode(11);
    head->next = createNode(11);
    head->next->next = createNode(12);
    head->next->next->next = createNode(21);
    head->next->next->next->next = createNode(41);
    head->next->next->next->next->next = createNode(43);
    head->next->next->next->next->next->next = createNode(21);

    head = removeDuplicates(head);
    printList(head);

    return 0;
}
