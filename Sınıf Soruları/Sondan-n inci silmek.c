#include <stdio.h>
#include <stdlib.h>

// Node yapısı
struct Node {
    int data;
    struct Node* next;
};

// Listenin sondan n. düğümünü silen fonksiyon
struct Node* deleteNthFromEnd(struct Node* head, int n) {
    struct Node* temp = head;
    int length = 0;

    // 1. Liste uzunluğunu bul
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    // Eğer silinmesi gereken düğüm listenin boyundan büyükse
    if (n > length) {
        printf("Geçersiz pozisyon!\n");
        return head;
    }

    // 2. Eğer ilk düğüm silinecekse
    if (n == length) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // 3. Silinecek düğüme kadar ilerle (length - n. düğüme kadar)
    temp = head;
    for (int i = 1; i < length - n; i++) {
        temp = temp->next;
    }

    // Silinecek düğüm
    struct Node* del = temp->next;
    
    // Bağlantıyı atla
    temp->next = del->next;

    // Hafızayı serbest bırak
    free(del);

    return head;
}

// Yardımcı fonksiyonlar (düğüm ekleme, listeyi yazdırma)
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    // Örnek liste oluşturma
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Orijinal Liste: ");
    printList(head);

    // Sondan 2. düğümü sil
    head = deleteNthFromEnd(head, 2);

    printf("Güncellenmiş Liste: ");
    printList(head);

    return 0;
}
