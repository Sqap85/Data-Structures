// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

// Düğüm yapısı
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Dairesel bağlı listenin başına eleman ekleme
Node* addFirst(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    if (head == NULL) {
        newNode->next = newNode; // İlk düğüm kendine işaret eder
        return newNode;
    }

    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next; // Dairenin sonuna kadar git
    }
    temp->next = newNode; // Son düğümün next'i yeni düğüme işaret eder
    newNode->next = head; // Yeni düğüm başa işaret eder
    head = newNode; // Listenin başını yeni düğüm olarak ayarla
    return head;
}

// Dairesel bağlı listenin sonuna eleman ekleme
Node* addLast(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    if (head == NULL) {
        newNode->next = newNode; // İlk düğüm kendine işaret eder
        return newNode;
    }

    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next; // Dairenin sonuna kadar git
    }
    temp->next = newNode; // Son düğümün next'i yeni düğüme işaret eder
    newNode->next = head; // Yeni düğüm başa işaret eder
    return head; // Başın adresini döndür
}

// Dairesel bağlı listenin başındaki düğümü silme
Node* removeFirst(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    Node* temp = head;
    if (head->next == head) { // Tek düğüm varsa
        free(head);
        return NULL; // Baş olarak null döndür
    }

    // Baş düğümden sonraki düğümü baş olarak ayarla
    Node* last = head;
    while (last->next != head) {
        last = last->next; // Dairenin sonuna git
    }

    head = head->next; // Baş düğümü güncelle
    last->next = head; // Son düğümün next'ini yeni başa işaret et
    free(temp); // Eski başı serbest bırak
    return head; // Yeni başı döndür
}

// Dairesel bağlı listenin sonundaki düğümü silme
Node* removeLast(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    Node* temp = head;
    if (head->next == head) { // Tek düğüm varsa
        free(head);
        return NULL; // Baş olarak null döndür
    }

    Node* prev = NULL;
    while (temp->next != head) {
        prev = temp; // Önceki düğümü kaydet
        temp = temp->next; // Dairenin sonuna git
    }

    free(temp); // Son düğümü serbest bırak
    prev->next = head; // Önceki düğümün next'ini başa işaret et
    return head; // Başın adresini döndür
}

// Belirli bir değere sahip düğümün sonrasına eleman ekleme
Node* insertAfterValue(Node* head, int newData, int targetData) {
    if (head == NULL) {
        return head; // Eğer liste boşsa, null döndür
    }

    Node* temp = head;
    do {
        if (temp->data == targetData) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = newData;
            newNode->next = temp->next; // Yeni düğümün next'i mevcut düğümün next'ine işaret eder
            temp->next = newNode; // Mevcut düğümün next'i yeni düğüme işaret eder
            return head; // Başın adresini döndür
        }
        temp = temp->next;
    } while (temp != head); // Dönmeyi durdur, dairenin başına geri döndükten sonra

    return head; // Hedef değer bulunamadı, değişiklik yapma
}

// Dairesel bağlı listedeki belirli bir değere sahip düğümü silme
Node* removeByValue(Node* head, int value) {
    if (head == NULL) {
        return head; // Eğer liste boşsa, null döndür
    }
    if (head->data == value) {
        if (head->next == head) {
            free(head);
            return NULL; // Baş olarak null döndür
        }
        Node* last = head;
        while (last->next != head) {
            last = last->next;
        }
        Node* deleted = head;
        last->next = deleted->next;
        head = head->next;
        free(deleted);
        return head;
    }
    Node* temp = head;
    while (temp->next != head && temp->next->data != value) {
        temp = temp->next;
    }
    if (temp->next == head) { return head; } // value değeri listede yok

    Node* deleted = temp->next;
    temp->next = deleted->next;
    free(deleted);
    return head;
}

// Dairesel bağlı listedeki tüm elemanları yazdırma
void printList(Node* head) {
    if (head == NULL) {
        printf("Liste boş.\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head); // Dairenin başına geri dönene kadar
    printf("Head\n"); // Baş düğümünü göster
}

// Listede kaç düğüm var
int printListCount(Node* head) {
    if (head == NULL) {
        return 0; // Liste boşsa
    }

    Node* temp = head;
    int count = 0;

    do {
        count++;
        temp = temp->next;
    } while (temp != head); // Dairenin başına geri dönene kadar

    return count; // Düğüm sayısını döndür
}

int main(void) {
    Node* head = NULL;
    int choice, data, position;

    do {
        printf("\n1. Başa eleman ekle\n");
        printf("2. Sona eleman ekle\n");
        printf("3. Belirli bir dataya sahip elemandan sonraya ekle\n");
        printf("4. Baştan eleman sil\n");
        printf("5. Sondan eleman sil\n");
        printf("6. Belirli bir dataya sahip elemanı sil\n");
        printf("7. Listeyi yazdır\n");
        printf("8. Liste eleman sayısını göster\n");
        printf("0. Çıkış\n");
        printf("Seçiminizi yapın: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                head = addFirst(head, data);
                break;
            case 2:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                head = addLast(head, data);
                break;
            case 3:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                printf("Hangi dataya sahip node'dan sonraya eklensin(data gir): ");
                scanf("%d", &position);
                head = insertAfterValue(head, data, position);
                break;
            case 4:
                head = removeFirst(head);
                break;
            case 5:
                head = removeLast(head);
                break;
            case 6:
                printf("Hangi dataya sahip olan silinecek(data gir): ");
                scanf("%d", &position);
                head = removeByValue(head, position);
                break;
            case 7:
                printList(head);
                break;
            case 8:
                printf("Liste eleman sayısı: %d\n", printListCount(head));
                break;
            case 0:
                printf("Çıkılıyor...\n");
                break;
            default:
                printf("Geçersiz seçim!\n");
                break;
        }
    } while (choice != 0);

    return 0; // Programı sonlandır
}
}
