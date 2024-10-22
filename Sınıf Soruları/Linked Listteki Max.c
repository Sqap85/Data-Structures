//Verilen listede maksimum degeri donduren fonksiyonu yaz
#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğüm yapısı
struct Node {
    int data;
    struct Node* next;
};

// Maksimum değeri bulan fonksiyon
int findMax(struct Node* head) {
    if (head == NULL) {
        printf("Liste boş!\n");
        return -1;  // Hata durumu
    }

    int max = head->data;  // İlk düğümdeki veriyi başlangıç olarak kabul et

    struct Node* current = head;  // Mevcut düğümü işaret eder

    while (current != NULL) {
        if (current->data > max) {
            max = current->data;  // Daha büyük bir değer bulunduğunda max güncellenir
        }
        current = current->next;  // Bir sonraki düğüme geç
    }

    return max;
}

// Yeni bir düğüm oluşturma fonksiyonu
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    // Bağlı listeyi oluşturma
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(15);

    // Maksimum değeri bul ve yazdır
    printf("Maksimum değer: %d\n", findMax(head));

    // Belleği serbest bırakmayı unutma
    free(head->next->next->next);
    free(head->next->next);
    free(head->next);
    free(head);

    return 0;
}