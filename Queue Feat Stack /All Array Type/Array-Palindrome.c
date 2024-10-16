
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Harf işlemleri için

/* verilen stringi polindrome olup olmadigini queue ve stack kullanarak belirleyen kod
Palindrome kontrolü için bir string’in baştan sona ve sondan başa aynı olup olmadığını kontrol ederiz. Bunu yapmak için, string’in karakterlerini sırayla bir queue‘ya (kuyruğa) ve bir stack‘e (yığına) ekleriz. Sonra queue’dan ve stack’ten sırayla karakterleri çıkartıp karşılaştırırız.
Queue ile string’in karakterlerini baştan sona doğru alırken, stack ile karakterleri sondan başa doğru alırız. Eğer tüm karşılaştırmalar aynıysa string bir palindrome’dur. 
*/

#define MAX 100  // Maksimum string uzunluğu

// Kuyruk yapısı
typedef struct Queue {
    int front, rear, counter;
    char data[MAX];
} Queue;

// Yığın (Stack) yapısı
typedef struct Stack {
    int top;
    char data[MAX];
} Stack;

// Kuyruğu başlatma
void initializeQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->counter = 0;
}

// Yığını başlatma
void initializeStack(Stack *s) {
    s->top = -1;
}

// Kuyruğun boş olup olmadığını kontrol etme
int isQueueEmpty(Queue *q) {
    return (q->counter == 0);
}

int isQueueFull(Queue *q){
    return (q->counter == MAX);
}

// Kuyruğa eleman ekleme (Enqueue)
void enqueue(Queue *q, int value) {
    if (isQueueFull(q)) {
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
    if (isQueueEmpty(q)) {
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

// Yığına eleman ekleme (Push)
void push(Stack *s, char value) {
    if (s->top < MAX - 1) {
        s->data[++(s->top)] = value;
    }
}

// Yığından eleman çıkarma (Pop)
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return '\0';  // Yığın boşsa null karakter döndür
}

// Palindrome kontrol fonksiyonu
int isPalindrome(char *str) {
    Queue q;
    Stack s;
    initializeQueue(&q);
    initializeStack(&s);
    
    // String'deki geçerli karakterleri sırayla hem kuyruğa hem yığına ekle
    for (int i = 0; i < strlen(str); i++) {
        if (isalnum(str[i])) {  // Sadece harf ve rakamları dikkate al
            char ch = tolower(str[i]);  // Büyük/küçük harf farkını ortadan kaldır
            enqueue(&q, ch);
            push(&s, ch);
        }
    }

    // Kuyruktan ve yığından çıkartılan elemanları karşılaştır
    while (!isQueueEmpty(&q)) {
        if (dequeue(&q) != pop(&s)) {
            return 0;  // Eğer bir eşleşmezlik bulunursa palindrome değildir
        }
    }

    return 1;  // Eğer tüm karakterler eşleşirse palindrome'dur
}

// Ana fonksiyon
int main() {
    char str[MAX];
    
    printf("Bir string girin: ");
    fgets(str, MAX, stdin);  // Kullanıcıdan string alma (fgets ile daha güvenli)

    if (isPalindrome(str)) {
        printf("'%s' bir palindromdur.\n", str);
    } else {
        printf("'%s' bir palindrom değildir.\n", str);
    }

    return 0;
}
