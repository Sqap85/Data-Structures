//85 is biggest.
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğümü yapısı
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Bağlı listenin sonuna eleman ekleme ve yeni başı döndürme
Node* addLast(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // Eğer liste boşsa, yeni düğümü baş olarak döndür
    }
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme kadar git
    }
    temp->next = newNode; // Son düğümün next'ine yeni düğümü ekle
    return head; // Başın adresini döndür
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
    Node* head = NULL;

    // Bağlı listeye eleman ekleme
    head = addLast(head, 1);
    head = addLast(head, 2);
    head = addLast(head, 3);
    head = addLast(head, 4);
    head = addLast(head, 5);

    // Bağlı listeyi yazdır
    printf("Bağlı liste: ");
    printList(head);

    // Döngü yaratmak için son düğümü ikinci düğüme bağla (test amaçlı)
    head->next->next->next->next->next = head->next;

    // Döngü tespiti yap
    if (detectCycle(head)) {
        printf("Bağlı listede döngü var!\n");
    } else {
        printf("Bağlı listede döngü yok!\n");
    }

    // Bellek sızıntısını önlemek için her düğüm için free() kullanılması önerilir.

    return 0;
}
