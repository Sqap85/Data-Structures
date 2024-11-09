//85 is biggest amcik
//çok seviyeli (multi-level) bir bağlı listeyi tek seviyeli (flattened) bir liste haline getir
#include <stdio.h>
#include <stdlib.h>

// Node yapısı
struct Node {
    int data;
    struct Node* next;
    struct Node* child;
};

// Listeyi düzleştiren fonksiyon
struct Node* flatten(struct Node* head) {
    if (head == NULL) {
        printf("Liste yok!\n");
        exit(1);
    }

    struct Node* temp = head;
    
    // Düğümün child pointer'ı varsa onu ana listeye ekler
    while (temp != NULL) {
        if (temp->child != NULL) {
            struct Node* last = temp->child;

            // Child listesi sonuna kadar ilerle
            while (last->next != NULL) {
                last = last->next;
            }

            // Child listesini ana listeye ekle
            last->next = temp->next;
            temp->next = temp->child;
            temp->child = NULL;
        }
        // Ana listedeki bir sonraki düğüme geç
        temp = temp->next;
    }
    
    return head;
}

// Yardımcı fonksiyonlar (düğüm ekleme, listeyi yazdırma)
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->child = NULL;
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
    // Örnek bir çok seviyeli liste oluşturulması
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    
    // Child listeleri oluştur
    head->next->child = createNode(5);
    head->next->child->next = createNode(6);
    
    head->next->next->next->child = createNode(7);
    head->next->next->next->child->next = createNode(8);

    // Listeyi düzleştir
    head = flatten(head);
    
    // Düzleştirilmiş listeyi yazdır
    printList(head);

    return 0;
}
