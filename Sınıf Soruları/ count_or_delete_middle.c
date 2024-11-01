//85 is biggest
//bağlı listenin düğüm sayısını hesaplar. Düğüm sayısı tekse ortadaki düğümü siler, çiftse düğüm sayısını ekrana yazdırır.
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;

// Düğüm sayısına göre ortadaki düğümü silme veya düğüm sayısını yazdırma fonksiyonu
void count_or_delete_middle(node *head) {
    int i = 0;
    node *p = head;

    while (p != NULL) {
        i++;
        p = p->next;
    }

    p = head;

    if (i % 2 == 1) { // Tekse ortadaki düğümü sil
        int a = i / 2 + 1;

        for (int j = 1; j < a; j++) {
            p = p->next;
        }

        if (p->prev != NULL) {
            p->prev->next = p->next;
        }
        if (p->next != NULL) {
            p->next->prev = p->prev;
        }

        free(p);
        printf("Orta düğüm silindi.\n");
    } else { // Çiftse düğüm sayısını yazdır
        printf("Düğüm sayısı: %d\n", i);
    }
}

// Çift bağlı listenin sonuna eleman ekleme fonksiyonu
node* addLast(node* head, int newData) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Listeyi yazdırma fonksiyonu
void printList(node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    node *head = NULL;

    // Bağlı listeyi oluşturma
    head = addLast(head, 3);
    head = addLast(head, 1);
    head = addLast(head, 4);
    head = addLast(head, 1);
    head = addLast(head, 5);

    printf("Orijinal Liste: ");
    printList(head);

    // Düğüm sayısına göre ortadaki düğümü sil veya düğüm sayısını yazdır
    count_or_delete_middle(head);

    printf("Güncellenmiş Liste: ");
    printList(head);

    return 0;
}