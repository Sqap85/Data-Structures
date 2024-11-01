// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

// Node yapısını tanımlama
typedef struct Node {
    int data;
    struct Node* next; // Sonraki düğüme işaretçi
    struct Node* prev; // Önceki düğüme işaretçi
} Node;

// Çift bağlı listenin başına eleman ekleme
Node* addFirst(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = head;
    newNode->prev = NULL; // Başta olduğu için önceki düğüm NULL

    if (head != NULL) {
        head->prev = newNode; // Eski başın prev'ini yeni düğüme bağla
    }

    return newNode; // Yeni düğüm yeni baş olur
}

// Çift bağlı listenin sonuna eleman ekleme
Node* addLast(Node* head, int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL; // Son olduğu için next NULL

    if (head == NULL) {
        newNode->prev = NULL; // Liste boşsa, prev de NULL
        return newNode; // Yeni düğüm baş olur
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme kadar git
    }

    temp->next = newNode;
    newNode->prev = temp; // Yeni düğümün prev'ini son düğüme bağla
    return head;
}

// Çift bağlı listenin başındaki düğümü silme
Node* removeFirst(Node* head) {
    if (head == NULL) {
        return NULL; // Liste boşsa, null döndür
    }

    Node* temp = head;
    head = head->next; // Başı bir sonrakine kaydır

    if (head != NULL) {
        head->prev = NULL; // Yeni başın prev'ini NULL yap
    }

    free(temp); // Eski başı serbest bırak
    return head;
}

// Çift bağlı listenin sonundaki düğümü silme
Node* removeLast(Node* head) {
    if (head == NULL) {
        return NULL; // Liste boşsa, null döndür
    }

    if (head->next == NULL) {
        free(head); // Tek düğüm varsa onu sil
        return NULL;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme git
    }

    temp->prev->next = NULL; // Önceki düğümün next'ini NULL yap
    free(temp); // Son düğümü serbest bırak
    return head;
}

// Çift bağlı listede belirli bir data değerinden sonraya yeni düğüm ekleme
Node* addAfterValue(Node* head, int targetData, int newData) {
    // Liste boşsa, doğrudan geri döndür
    if (head == NULL) {
        return head;
    }

    Node* temp = head;

    // Listede targetData'yi bul
    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    // Eğer targetData bulunamadıysa, değişiklik yapma
    if (temp == NULL) {
        return head; // Değer bulunamadı, listeyi olduğu gibi döndür
    }

    // Yeni düğüm oluştur
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    // Yeni düğümün next'ini mevcut düğümün next'ine bağla
    newNode->next = temp->next;
    newNode->prev = temp;

    // Eğer mevcut düğümün bir sonrakisi varsa, onun prev'i de yeni düğümü gösterecek
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }

    // Mevcut düğümün next'ini yeni düğüme bağla
    temp->next = newNode;

    return head; // Başın adresini döndür
}

// Çift bağlı listede belirli bir dataya sahip düğümü silme
Node* removeByValue(Node* head, int value) {
    if (head == NULL) { // Silinecek değer yok
        return head;
    }

    // Eğer silinecek düğüm baştaysa
    if (head->data == value) {
        Node *deleted = head;
        head = head->next;
        if (head != NULL) { 
            head->prev = NULL;
        }
        free(deleted);
        return head;
    }

    Node *temp = head;
    // Silinecek düğümü bulana kadar listede gezin
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        return head; // Değer listede yok
    }

    Node *deleted = temp->next;
    temp->next = deleted->next;
    if (deleted->next != NULL) {
        deleted->next->prev = temp; // Silinen düğümden sonra olanın prev'ini güncelle
    }
     
    free(deleted);
    return head;
}

// Çift bağlı listedeki tüm elemanları yazdırma
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Listede kaç düğüm var
int countListItems(Node* head) {
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
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
                printf("Hangi dataya sahip node dan sonraya eklensin (data gir): ");
                scanf("%d", &position);
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                head = addAfterValue(head, position, data);
                break;
            case 4:
                head = removeFirst(head);
                break;
            case 5:
                head = removeLast(head);
                break;
            case 6:
                printf("Silinecek datayı girin: ");
                scanf("%d", &data);
                head = removeByValue(head, data);
                break;
            case 7:
                printList(head);
                break;
            case 8:
                printf("Liste eleman sayısı: %d\n", countListItems(head));
                break;
            case 0:
                printf("Çıkılıyor...\n");
                break;
            default:
                printf("Geçersiz seçim!\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
