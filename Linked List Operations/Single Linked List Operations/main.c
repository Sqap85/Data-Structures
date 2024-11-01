//85 is biggest.
#include <stdio.h>
#include <stdlib.h>

// struct Node'a typedef kullanarak yeni isim veriyoruz: Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Bağlı listenin başına eleman ekleme ve yeni başı döndürme
Node* addFirst(Node* head, int newData) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = head; // Yeni düğümü başa ekliyoruz
    head = newNode; // yeni head
    return head; // Yeni başı döndür
}

// Bağlı listenin sonuna eleman ekleme ve yeni başı döndürme
Node* addLast(Node* head, int newData) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // Eğer liste boşsa, yeni düğümü baş olarak döndür
    }
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // Son düğüme kadar git
    }
    temp->next = newNode; // Son düğümün next'ine yeni düğümü ekle
    return head; // Başın adresini döndür
}

// Bağlı listedeki baştaki düğümü silme
Node* removeFirst(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    Node* temp = head; // Baş düğüm
    head = head->next; // Başı bir sonraki düğüm yap
    free(temp); // Eski başı serbest bırak
    return head; // Yeni başı döndür
}

// Bağlı listedeki son düğümü silme
Node* removeLast(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    // Eğer yalnızca bir düğüm varsa
    if (head->next == NULL) {
        free(head); // Tek düğümü serbest bırak
        return NULL; // Baş olarak null döndür
    }

    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next; // Son iki düğüme kadar git
    }

    free(temp->next); // Son düğümü serbest bırak
    temp->next = NULL; // Son düğümün next'ini null yap
    return head; // head döndür
}

// Tek bağlı listenin belirli bir değere sahip düğümün sonrasına eleman ekleme
Node* addAfterValue(Node* head, int newData, int targetData) {
    if (head == NULL) {
        return head; // Eğer liste boşsa, null döndür
    }

    Node* temp = head;

    // targetData değerini bul
    while (temp != NULL && temp->data != targetData) {
        temp = temp->next;
    }

    // Eğer targetData bulunamazsa, head'i geri döndür
    if (temp == NULL) {
        return head; // Hedef değer bulunamadı, değişiklik yapma
    }

    // Yeni düğüm oluştur
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    // Yeni düğümün bağlantılarını ayarla
    newNode->next = temp->next; // Yeni düğümün next'i, mevcut düğümün next'ine işaret eder
    temp->next = newNode; // Mevcut düğümün next'i yeni düğüme işaret eder

    return head; // Başın adresini döndür
}

// Bağlı listedeki belirli bir değere sahip elemanı silme
Node* removeByValue(Node* head, int value) {
    if (head == NULL) {
        return head; // Eğer liste boşsa
    }

    Node* temp = head;
    // Eğer silinmesi gereken düğüm baştaysa
    if (head->data == value) {
        Node* temp = head;
        head = head->next; // Başın bir sonrakine kaydırılması
        free(temp); // Eski baş düğümü serbest bırak
        return head;
    }

    // Listede gezin ve değeri bulmaya çalış
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }

    // Eğer temp->next NULL ise, değer listede yoktur
    if (temp->next == NULL) {
        return head; // Değer bulunamadı, listeyi olduğu gibi döndür
    }

    // Değeri bulduk, silme işlemini yap
    Node* deleted = temp->next;
    temp->next = deleted->next; // Silinen düğümden bir sonrakine geçiş
    free(deleted); // Düğümü serbest bırak

    return head; // Başın adresini döndür
}

// Bağlı listedeki tüm elemanları yazdırma
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Listede kaç düğüm var
int countListItems(Node *head){
    Node *temp = head;
    int count=0;
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
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                printf("Hangi dataya sahip node dan sonraya eklensin(data gir): ");
                scanf("%d", &position);
                head = addAfterValue(head, data,position);
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
