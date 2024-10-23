// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğümü yapısı (typedef ile)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Yeni düğüm oluşturma
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Döngü olup olmadığını tespit eden Floyd’un Döngü Algoritması
int detectCycle(Node* head) {
    Node *tortoise = head, *hare = head;

    while (hare != NULL && hare->next != NULL) {
        tortoise = tortoise->next;         // Kaplumbağa bir adım ilerler
        hare = hare->next->next;           // Tavşan iki adım ilerler

        // Kaplumbağa ve tavşan aynı düğümde buluşursa döngü vardır
        if (tortoise == hare) {
            return 1; // Döngü tespit edildi
        }
    }

    return 0; // Döngü tespit edilmedi
}

// Bağlı listeyi yazdırma fonksiyonu (test için)
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Ana fonksiyon
int main(void) {
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);

    // Döngü yaratmak için son düğümü ikinci düğüme bağla (test amaçlı)
    head->next->next->next->next->next = head->next;

    // Döngü tespiti yap
    if (detectCycle(head)) {
        printf("Bağlı listede döngü var!\n");
    } else {
        printf("Bağlı listede döngü yok!\n");
    }

    return 0;
}
