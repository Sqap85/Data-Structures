/*İki sıralı bağlı listeyi birleştirip yeni bir sıralı liste döndüren bir fonksiyon yaz */
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğüm yapısı
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Listeye sonuna düğüm ekleyen fonksiyon
void addLast(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        // Liste boşsa, yeni düğüm baş olur
        *head = newNode;
    } else {
        // Liste doluysa, son düğümü bul
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Son düğümün next alanına yeni düğümü ekle
        temp->next = newNode;
    }
}

// İki sıralı listeyi birleştiren fonksiyon
Node* mergeSortedLists(Node* head1, Node* head2) {
    Node* newHead = NULL;  // Yeni liste başlangıcı

    // İki listeyi birleştiriyoruz
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            addLast(&newHead, head1->data);
            head1 = head1->next;
        } else {
            addLast(&newHead, head2->data);
            head2 = head2->next;
        }
    }

    // Kalan elemanları ekle (eğer varsa)
    while (head1 != NULL) {
        addLast(&newHead, head1->data);
        head1 = head1->next;
    }
    while (head2 != NULL) {
        addLast(&newHead, head2->data);
        head2 = head2->next;
    }

    return newHead;
}

// Yeni bir düğüm oluşturma fonksiyonu (sadece örnek için)
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
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
    // İlk sıralı listeyi oluşturma: 1 -> 3 -> 5
    Node* head1 = createNode(1);
    head1->next = createNode(3);
    head1->next->next = createNode(5);

    // İkinci sıralı listeyi oluşturma: 2 -> 4 -> 6
    Node* head2 = createNode(2);
    head2->next = createNode(4);
    head2->next->next = createNode(6);

    // İki sıralı listeyi birleştirme
    Node* newHead = mergeSortedLists(head1, head2);

    // Birleştirilmiş listeyi yazdırma
    printf("Birleştirilmiş liste: ");
    printList(newHead);

    // Belleği serbest bırakmayı unutma
    free(head1->next->next);
    free(head1->next);
    free(head1);

    free(head2->next->next);
    free(head2->next);
    free(head2);

    // Yeni birleştirilmiş listenin elemanlarını serbest bırakmayı unutma
    while (newHead != NULL) {
        Node* temp = newHead;
        newHead = newHead->next;
        free(temp);
    }

    return 0;
}