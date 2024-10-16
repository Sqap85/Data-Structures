#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Kuyruğun maksimum kapasitesi

// Kuyruk yapısını typedef ile tanımlama
typedef struct Queue {
    int data[MAX];
    int front;
    int rear;
    int counter;  // Kuyruktaki eleman sayısını tutan sayaç
} Queue;

// Kuyruğu başlatma
void initialize(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->counter = 0;  // Başlangıçta kuyruk boş olduğundan sayaç 0
}

// Kuyruğun dolu olup olmadığını kontrol etme
int isFull(Queue *q) {
    return (q->counter == MAX);
}

// Kuyruğun boş olup olmadığını kontrol etme
int isEmpty(Queue *q) {
    return (q->counter == 0);
}

// Kuyruğa eleman ekleme (Enqueue)
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Kuyruk dolu!\n");
    } else {
        q->rear++;
        q->counter++;
        if (q->rear == MAX) {
            q->rear = 0;
        }
        q->data[q->rear] = value;
    }
}

// Kuyruktan eleman çıkarma (Dequeue)
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyruk boş!\n");
        return -1;
    } else {
        int x = q->data[q->front];
        q->front++;
        q->counter--;
        if (q->front == MAX) {
            q->front = 0;
        }
        return x;
    }
}

// Kuyruğun içeriğini görüntüleme
void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Kuyruk boş!\n");
    } else {
        printf("Kuyruktaki elemanlar: \n");
        for (int i = 0; i < q->counter; i++) {
            int index = (q->front + i) % MAX; // Circular index
            printf("%d ", q->data[index]);
        }
        printf("\n");
    }
}

int main() {
    Queue *q = (Queue *)malloc(sizeof(Queue));  // Kuyruk için bellek ayırma
    initialize(q);  // Kuyruğu başlatma

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);

    display(q);

    dequeue(q);
    dequeue(q);

    display(q);

    free(q);  // Belleği serbest bırakma
    return 0;
}
