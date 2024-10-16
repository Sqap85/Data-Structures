#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100  // Maksimum string boyutu

// Kuyruk düğüm yapısı
typedef struct Node {
    char data;
    struct Node *next;  // Bir sonraki düğümün işaretçisi
} Node;

// Kuyruk yapısı
typedef struct Queue {
    Node *front;      // Ön düğüm
    Node *rear;       // Arka düğüm
    int counter;      // Kuyruktaki eleman sayısını tutan sayaç
} Queue;

typedef struct {
    Node* top;
} Stack;

// Yığın fonksiyonları
void initStack(Stack* s) {
    s->top = NULL;
}

int isStackEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = c;
        newNode->next = s->top;
        s->top = newNode;
    }
}

char pop(Stack* s) {
    if (isStackEmpty(s)) {
        return '\0'; // Yığın boşsa hata durumu
    }
    Node* temp = s->top;
    char data = temp->data;
    s->top = s->top->next;
    free(temp); // Belleği temizle
    return data;
}

// Kuyruk fonksiyonları
void initializeQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->counter = 0;      // Başlangıçta kuyruk boş olduğundan sayaç 0
}

int isQueueEmpty(Queue *q) {
    return q->counter == 0;
}

void enqueue(Queue *q, char value) {
    Node *temp = (Node *)malloc(sizeof(Node));  // Yeni düğüm oluşturma
    temp->data = value;
    temp->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = temp;  // Ön düğüm ilk eleman
        q->rear = temp;   // Arka düğüm ilk eleman
    } else {
        q->rear->next = temp;  // Önceki arka düğümün yanına yeni düğümü ekle
        q->rear = temp;        // Arka düğümü güncelle
    }
    q->counter++;  // Sayaç değerini artır
}

char dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return '\0';  // Kuyruk boşsa hata durumu
    } else {
        char x = q->front->data;
        Node *deleted = q->front;
        q->front = deleted->next;
        free(deleted);
        q->counter--;
        return x;  // Çıkarılan değeri döndür
    }
}

// Palindrome kontrolü
int isPalindrome(char *str) {
    Queue q;
    Stack s;
    initializeQueue(&q);
    initStack(&s);

    // Kuyruğa ve yığına karakterleri ekle
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);  // Büyük-küçük harf farkını yok saymak için
        if (isalnum(ch)) {  // Sadece alfanumerik karakterleri dikkate al
            enqueue(&q, ch);
            push(&s, ch);
        }
    }

    // Kuyruk ve yığın ile karşılaştırma
    while (!isQueueEmpty(&q) && !isStackEmpty(&s)) {
        char fromQueue = dequeue(&q);
        char fromStack = pop(&s);
        if (fromQueue != fromStack) {
            return 0;  // Eşleşme yoksa palindrome değil
        }
    }
    return 1;  // Tüm karakterler eşleşirse palindrome'dur
}

// Ana fonksiyon
int main() {
    char str[MAX_SIZE];
    printf("Bir string girin: ");
    fgets(str, MAX_SIZE, stdin);  // String girişi al

    // Son karakterin '\n' olup olmadığını kontrol et
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';  // '\n' karakterini kaldır
    }

    if (isPalindrome(str)) {
        printf("'%s' bir palindrome'dur.\n", str);
    } else {
        printf("'%s' bir palindrome değildir.\n", str);
    }

    return 0;
}