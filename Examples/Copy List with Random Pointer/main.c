// 85 is biggest.
/*
 Rastgele işaretçi (random pointer) olan bağlı bir listeyi kopyalama sorusu, klasik bir bağlı liste probleminin daha karmaşık bir versiyonudur. Normal bir bağlı listede her düğüm sadece bir sonraki düğümü (next pointer) işaret ederken, bu problemde her düğümün ayrıca rastgele bir düğümü işaret eden bir “random pointer”ı (işaretçisi) vardır. Bu rastgele işaretçi, listedeki herhangi bir düğümü veya NULL’ı gösterebilir.

 Problem Açıklaması:

 Bu tür bir listeyi kopyalamamız isteniyor. Ancak burada iki şey göz önünde bulundurulmalıdır:

     1.    Bağlı listenin next işaretçileri aynı sırayı takip eder.
     2.    Her düğümün rastgele bir düğüme işaret eden bir random işaretçisi vardır, bu da kopyalanmalıdır.

    Adımlar:
    1.    Aşama 1: Orijinal listenin her düğümünü klonlayarak, orijinal düğümlerin hemen yanına yerleştiririz.
     •    Örneğin, orijinal liste şu haldeyse: 1 -> 2 -> 3 -> NULL
     •    İlk adımda şu hale gelir: 1 -> 1' -> 2 -> 2' -> 3 -> 3' -> NULL
     2.    Aşama 2: Orijinal listenin random işaretçilerini kopyalayarak yeni düğümlere ayarlarız.
     •    Yani, orijinal düğümün random işaretçisi nereye işaret ediyorsa, klon düğümün random işaretçisi de kopyalanmış haline işaret edecektir.
     •    Örneğin, 1.random = 3 ise, 1'.random = 3' olacak.
     3.    Aşama 3: Yeni ve orijinal listeyi birbirinden ayırırız, böylece her iki liste de kendi başına çalışabilir.
*/

#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğüm yapısı
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* random;
} Node;

// Yeni düğüm oluşturma
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->random = NULL;
    return node;
}

// Bağlı listeyi yazdırma (next ve random işaretçileri ile)
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("Düğüm: %d, Random: %d\n", temp->data, temp->random ? temp->random->data : -1);
        temp = temp->next;
    }
}

// Listeyi rastgele işaretçilerle kopyalama fonksiyonu
Node* copyRandomList(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* current = head;

    // Aşama 1: Her orijinal düğümden sonra bir kopyasını ekle
    while (current != NULL) {
        Node* temp = newNode(current->data);
        temp->next = current->next;
        current->next = temp;
        current = temp->next;
    }

    // Aşama 2: Random işaretçileri ayarla
    current = head;
    while (current != NULL) {
        if (current->random != NULL) {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    // Aşama 3: Orijinal liste ve kopyayı ayır
    Node* newHead = head->next;
    Node* copy = newHead;
    current = head;
    while (current != NULL) {
        current->next = current->next->next;
        if (copy->next != NULL) {
            copy->next = copy->next->next;
        }
        current = current->next;
        copy = copy->next;
    }

    return newHead;
}

int main(void) {
    // Orijinal listeyi oluştur
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);

    // Random işaretçileri ayarla
    head->random = head->next->next; // 1 -> 3
    head->next->random = head; // 2 -> 1

    printf("Orijinal Liste:\n");
    printList(head);

    Node* newHead = copyRandomList(head);

    printf("Kopyalanmış Liste:\n");
    printList(newHead);

    return 0;
}
