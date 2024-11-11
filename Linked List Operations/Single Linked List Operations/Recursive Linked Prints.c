#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to add a node at the end of the list
Node* addLast(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (head == NULL) {
        return newNode;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Recursive function to print the list in reverse order
void reversePrint(Node* head) {
    if (head == NULL) {
        return;
    }
    reversePrint(head->next); // Recursive call for the next node
    printf("%d ", head->data); // Print the data of the current node
}

// Recursive function to print the list in order
void printList(Node* head) {
    if (head == NULL) {
        return;
    }
    printf("%d ", head->data); // Print the data of the current node
    printList(head->next); // Recursive call for the next node
}

int main() {
    Node* head = NULL;
    
    // Add nodes to the list
    head = addLast(head, 10);
    head = addLast(head, 20);
    head = addLast(head, 30);
    head = addLast(head, 40);
    
    // Print the list in normal order
    printf("List in order: ");
    printList(head);
    printf("\n");

    // Print the list in reverse order
    printf("List in reverse order: ");
    reversePrint(head);
    printf("\n");

    // Free the memory
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}