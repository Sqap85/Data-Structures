//85 is biggest
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Yığın düğümü
struct Node {
    char data;
    struct Node* next;
};

// Yığın yapısı
struct Stack {
    struct Node* top;
};

// Yığın işlemleri
void initStack(struct Stack* s) {
    s->top = NULL;
}

int isEmpty(struct Stack* s) {
    return s->top == NULL;
}

void push(struct Stack* s, char item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Bellek hatası!\n");
        return;
    }
    newNode->data = item;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Yığın boş\n");
        return '\0';
    }
    struct Node* temp = s->top;
    char popped = temp->data;
    s->top = s->top->next;
    free(temp);
    return popped;
}

char peek(struct Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->top->data;
}

int isOperand(char ch) {
    return isalnum(ch);  // Harf veya sayı olup olmadığını kontrol eder
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// İfadeyi postfix'e dönüştür
void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initStack(&s);
    
    int k = 0; // Postfix dizisinin indeksi
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        
        // Eğer operand ise sonucu yaz
        if (isOperand(ch)) {
            postfix[k++] = ch;
        }
        // Eğer sol parantez ise yığına koy
        else if (ch == '(') {
            push(&s, ch);
        }
        // Eğer sağ parantez ise sol paranteze ulaşana kadar çıkar
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);  // Sol parantezi çıkar
        }
        // Operatör ile karşılaşılırsa
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[k++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    // Kalan operatörleri yığından çıkar
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    
    postfix[k] = '\0';  // Null sonlandırıcı ekle
}

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Infix ifadeyi girin: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix ifade: %s\n", postfix);
    
    return 0;
}
