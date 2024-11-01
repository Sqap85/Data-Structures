//85 is biggest.
//Verilen bir bağlı listede en küçük değeri tüm düğümlerden (head dahil) çıkaran fonksiyon.
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

// En küçük değeri tüm düğümlerden çıkaran fonksiyon
node *subtractmin(node *head) {
    node *temp = head;
    int min = head->data;

    // Minimum değeri bulma
    while (temp != NULL) {
        if (min > temp->data) {
            min = temp->data;
        }
        temp = temp->next;
    }

    // Tüm düğümlerdeki değerlerden minimum değeri çıkarma
    temp = head;
    while (temp != NULL) {
        temp->data = temp->data - min;
        temp = temp->next;
    }

    return head;
}

// Bağlı listenin sonuna eleman ekleme ve yeni başı döndürme
node* addLast(node* head, int newData) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // Eğer liste boşsa, yeni düğümü baş olarak döndür
    }

    node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme kadar git
    }
    temp->next = newNode; // Son düğümün next'ine yeni düğümü ekle
    return head; // Başın adresini döndür
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

    // En küçük değeri çıkarma
    head = subtractmin(head);

    printf("En küçük değer çıkarıldıktan sonra Liste: ");
    printList(head);

    return 0;
}