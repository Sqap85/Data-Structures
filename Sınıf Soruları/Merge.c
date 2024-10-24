/*İki sıralı bağlı listeyi birleştirip yeni bir sıralı liste döndüren bir fonksiyon yaz */
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğüm yapısı
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Listeye sonuna düğüm ekleyen fonksiyon (yeni başı döndüren)
Node* addLast(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // Eğer liste boşsa, yeni düğümü baş olarak döndür
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme kadar git
    }

    temp->next = newNode; // Son düğümün next'ine yeni düğümü ekle
    return head; // Başın adresini döndür
}

// İki sıralı listeyi birleştiren fonksiyon
Node* mergeSortedLists(Node* head1, Node* head2) {
    Node* newHead = NULL;  // Yeni birleştirilmiş liste

    // İki listeyi birleştiriyoruz
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            newHead = addLast(newHead, head1->data); // Yeni başı döndürüyoruz
            head1 = head1->next;
        } else {
            newHead = addLast(newHead, head2->data);
            head2 = head2->next;
        }
    }

    // Kalan elemanları ekle (eğer varsa)
    while (head1 != NULL) {
        newHead = addLast(newHead, head1->data);
        head1 = head1->next;
    }

    while (head2 != NULL) {
        newHead = addLast(newHead, head2->data);
        head2 = head2->next;
    }

    return newHead;
}

// Bir bağlı listeyi yazdırma fonksiyonu
void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;

    // İlk sıralı listeyi oluşturma: 1 -> 3 -> 5
    head1 = addLast(head1, 1);
    head1 = addLast(head1, 3);
    head1 = addLast(head1, 5);

    // İkinci sıralı listeyi oluşturma: 2 -> 4 -> 6
    head2 = addLast(head2, 2);
    head2 = addLast(head2, 4);
    head2 = addLast(head2, 6);

    // İlk listeyi yazdırma
    printf("Liste 1: ");
    printList(head1);

    // İkinci listeyi yazdırma
    printf("Liste 2: ");
    printList(head2);

    // İki sıralı listeyi birleştirme
    Node* newHead = mergeSortedLists(head1, head2);

    // Birleştirilmiş listeyi yazdırma
    printf("Birleştirilmiş liste: ");
    printList(newHead);

    // Belleği serbest bırakmayı unutma
    while (newHead != NULL) {
        Node* temp = newHead;
        newHead = newHead->next;
        free(temp);
    }

    return 0;
}
