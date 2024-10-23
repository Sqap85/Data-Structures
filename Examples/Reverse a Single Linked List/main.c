// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Stack boyutunu belirle

// Single linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Yığın yapısı
typedef struct Stack {
    int top;
    int data[MAX];
} Stack;

// Yeni düğüm oluşturma
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Yığın başlatma
void initStack(Stack* s) {
    s->top = -1;
}

// Yığına veri ekleme (Push)
void Push(Stack* s, int data) {
    if (s->top == MAX - 1) {
        printf("Yığın dolu!\n");
        return;
    }
    s->data[++s->top] = data;
}

// Yığından veri çıkarma (Pop)
int Pop(Stack* s) {
    if (s->top == -1) {
        printf("Yığın boş!\n");
        return -1;
    }
    return s->data[s->top--];
}

// Bağlı listeyi tersine çeviren fonksiyon
Node* reverseList(Node* head) {
    if (head == NULL) return head;

    Stack s;
    initStack(&s);
    Node* temp = head;

    // Tüm düğümleri yığına ekle
    while (temp != NULL) {
        Push(&s, temp->data);
        temp = temp->next;
    }

    // Yığından çıkararak verileri ters sırayla düğümlere geri koy
    temp = head;
    while (temp != NULL) {
        temp->data = Pop(&s);
        temp = temp->next;
    }

    return head;
}

// Bağlı listeyi yazdırma fonksiyonu
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main(void) {
    Node* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);

    printf("Orijinal Bağlı Liste: ");
    printList(head);

    // Bağlı listeyi tersine çevir
    head = reverseList(head);

    printf("Tersine Çevrilmiş Bağlı Liste: ");
    printList(head);

    return 0;
}
