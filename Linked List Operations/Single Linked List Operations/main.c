//85 is biggest
#include <stdio.h>
#include <stdlib.h>

// struct Node'a typedef kullanarak yeni isim veriyoruz: Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Bağlı listenin başına eleman ekleme ve yeni başı döndürme
Node* insertAtBeginning(Node* head, int newData) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = head; // Yeni düğümü başa ekliyoruz
    head = newNode; // yeni head
    return head; // Yeni başı döndür
}

// Bağlı listenin sonuna eleman ekleme ve yeni başı döndürme
Node* insertAtEnd(Node* head, int newData) {
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
Node* deleteFromBeginning(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    Node* temp = head; // Baş düğüm
    head = head->next; // Başı bir sonraki düğüm yap
    free(temp); // Eski başı serbest bırak
    return head; // Yeni başı döndür
}

// Bağlı listedeki son düğümü silme
Node* deleteFromEnd(Node* head) {
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
Node* insertAfterValue(Node* head, int newData, int targetData) {
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

// Bağlı listedeki belirli bir konumdan eleman silme
Node* deleteByValue(Node* head, int value) {
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
int printListCount(Node *head){
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
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                printf("Hangi dataya sahip node dan sonraya eklensin(data gir): ");
                scanf("%d", &position);
                head = insertAfterValue(head, data,position);
                break;
            case 4:
                head = deleteFromBeginning(head);
                break;
            case 5:
                head = deleteFromEnd(head);
                break;
            case 6:
                printf("hangi dataya sahibi olan silinecek(data gir): ");
                scanf("%d", &position);
                head = deleteByValue(head, position);
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

    // Belleği serbest bırakma kısmını eklemek isteyebilirsiniz.
    return 0;
}

    int data;
    struct Node* next;
} Node;

// Bağlı listenin başına eleman ekleme ve yeni başı döndürme
Node* insertAtBeginning(Node* head, int newData) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = head; // Yeni düğümü başa ekliyoruz
    head = newNode; // yeni head
    return head; // Yeni başı döndür
}

// Bağlı listenin sonuna eleman ekleme ve yeni başı döndürme
Node* insertAtEnd(Node* head, int newData) {
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
Node* deleteFromBeginning(Node* head) {
    if (head == NULL) {
        return NULL; // Eğer liste boşsa, null döndür
    }

    Node* temp = head; // Baş düğüm
    head = head->next; // Başı bir sonraki düğüm yap
    free(temp); // Eski başı serbest bırak
    return head; // Yeni başı döndür
}

// Bağlı listedeki son düğümü silme
Node* deleteFromEnd(Node* head) {
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

// Bağlı listenin belirli bir konumuna eleman ekleme
Node* insertAtPosition(Node* head, int newData, int position) {
    // Eğer liste boşsa veya pozisyon 0 ise başa ekle
    if (position == 0) {
        return insertAtBeginning(head, newData);
    }

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = newData;
    Node* temp = head;

    // Pozisyonun sınırlarını kontrol et
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // Eğer temp null ise pozisyon listedeki toplam düğüm sayısından büyük demektir
    if (temp == NULL) {
        return head; // Geçersiz pozisyon, değişiklik yapma
    }

    // Yeni düğüm ekleniyor
    newNode->next = temp->next;
    temp->next = newNode;

    return head; // Başın adresini döndür
}

// Bağlı listedeki belirli bir konumdan eleman silme
Node* deleteByValue(Node* head, int value) {
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
int printListCount(Node *head){
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
        printf("3. Belirli bir pozisyona eleman ekle\n");
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
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Eklenecek veriyi girin: ");
                scanf("%d", &data);
                printf("Pozisyonu girin: ");
                scanf("%d", &position);
                head = insertAtPosition(head, data, position);
                break;
            case 4:
                head = deleteFromBeginning(head);
                break;
            case 5:
                head = deleteFromEnd(head);
                break;
            case 6:
                printf("hangi dataya sahibi olan silinecek(data gir): ");
                scanf("%d", &position);
                head = deleteByValue(head, position);
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

    // Belleği serbest bırakma kısmını eklemek isteyebilirsiniz.
    return 0;
}
