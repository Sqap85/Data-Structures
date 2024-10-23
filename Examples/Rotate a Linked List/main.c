/*
Eğer bir bağlı listeyi belirli bir noktadan itibaren döndürmek istiyorsak, önce o noktaya kadar olan elemanları sonuna taşımamız gerekir.
•    Örneğin, bağlı liste şu şekilde olsun: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
•    Eğer bu listeyi 2. düğüme göre döndürürsek, şu sonuç ortaya çıkar: 3 -> 4 -> 5 -> 1 -> 2 -> NULL
•    Eğer bu listeyi 4. düğüme göre döndürürsek, sonuç şu şekilde olur: 5 -> 1 -> 2 -> 3 -> 4 -> NULL

Döndürme Algoritmasının Adımları:

1.  Döndürme pozisyonuna göre listede gezerek o noktaya          ulaşılır.
2.  O noktadan sonrasını liste başı yapıp, kalan kısmı sona      eklenir.
3.  Yeni listenin sonunu (NULL) işaret ederiz.
*/
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğümü yapısı
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

// Bağlı listeyi döndürme fonksiyonu
Node* rotateList(Node* head, int k) {
    if (head == NULL || k == 0) {
        return head;
    }

    Node* current = head;
    int length = 1;

    // Listenin sonuna kadar git ve uzunluğu hesapla
    while (current->next != NULL) {
        current = current->next;
        length++;
    }

    // Listeyi döngüsel hale getir
    current->next = head;

    // Döndürme pozisyonu için k değerini listenin uzunluğuna göre mod al
    k = k % length;
    int stepsToNewHead = length - k;

    // Yeni başa kadar git
    Node* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }

    // Yeni başı ve sonu belirle
    Node* newHead = newTail->next;
    newTail->next = NULL;

    return newHead;
}

// Bağlı listeyi yazdırma fonksiyonu
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

    printf("Orijinal Liste: ");
    printList(head);

    int k = 2; // 2 düğüm kadar döndür
    head = rotateList(head, k);

    printf("%d düğüm kadar döndürülmüş liste: ", k);
    printList(head);

    return 0;
}
