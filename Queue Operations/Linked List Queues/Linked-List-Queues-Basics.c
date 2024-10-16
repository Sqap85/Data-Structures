#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5  // Maksimum kuyruk kapasitesi

// Kuyruk düğüm yapısı
typedef struct Node {
    int data;
    struct Node *next;  // Bir sonraki düğümün işaretçisi
} Node;

// Kuyruk yapısı
typedef struct Queue {
    Node *front;      // Ön düğüm
    Node *rear;       // Arka düğüm
    int counter;      // Kuyruktaki eleman sayısını tutan sayaç
} Queue;

// Kuyruğu başlatma
void initialize(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->counter = 0;      // Başlangıçta kuyruk boş olduğundan sayaç 0
}

// Kuyruğun dolu olup olmadığını kontrol etme
int isFull(Queue *q) {
    return q->counter == MAX_SIZE; // Eleman sayısı maksimum kapasiteye eşit mi?
}

// Kuyruğun boş olup olmadığını kontrol etme
int isEmpty(Queue *q) {
    return q->counter == 0;
}

// Kuyruğa eleman ekleme (Enqueue)
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Kuyruk dolu!\n");
        return; // Kuyruk doluysa ekleme yapma
    }

    Node *temp = (Node *)malloc(sizeof(Node));  // Yeni düğüm oluşturma
    temp->data = value;
    temp->next = NULL;

    if (isEmpty(q)) {
        // Kuyruk boşsa
        q->front = temp;  // Ön düğüm ilk eleman
        q->rear = temp;   // Arka düğüm ilk eleman
    } else {
        // Kuyrukta eleman varsa
        q->rear->next = temp;  // Önceki arka düğümün yanına yeni düğümü ekle
        q->rear = temp;        // Arka düğümü güncelle
    }
    q->counter++;  // Sayaç değerini artır
}

// Kuyruktan eleman çıkarma (Dequeue)
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyruk boş!\n");
        return -1;  // Kuyruk boşsa -1 döndür
    } else {
        int x = q->front->data;
        Node *deleted = q->front;
        q->front = deleted->next;
        free(deleted);
        q->counter--;
        if (isEmpty(q)) {
            q->rear = NULL;  // Kuyruk boşsa arka düğümü NULL yap
        }
        return x;  // Çıkarılan değeri döndür
    }
}

// Kuyruktaki eleman sayısını döndürme
int size(Queue *q) {
    return q->counter;  // Sayaç değerini döndür
}

// Kuyruğun içeriğini görüntüleme
void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyruk boş!\n");
    } else {
        printf("Kuyruktaki elemanlar: ");
        Node *current = q->front;  // Ön düğümden başlayarak gez
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;  // Sonraki düğüme geç
        }
        printf("\n");
    }
}

// Ana fonksiyon
int main() {
    Queue *q = (Queue *)malloc(sizeof(Queue));  // Kuyruk için bellek ayırma
    initialize(q);  // Kuyruğu başlatma

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);

    display(q);
    printf("Kuyruktaki eleman sayısı: %d\n", size(q)); // Eleman sayısını yazdır

    printf("Çıkarılan eleman: %d\n", dequeue(q));
    printf("Çıkarılan eleman: %d\n", dequeue(q));

    display(q);
    printf("Kuyruktaki eleman sayısı: %d\n", size(q)); // Eleman sayısını yazdır

    free(q);  // Belleği serbest bırakma
    return 0;
}
