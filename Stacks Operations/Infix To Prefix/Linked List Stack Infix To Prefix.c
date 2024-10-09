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

// İfadeyi ters çevirir
void reverse(char* exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - i - 1];
        exp[n - i - 1] = temp;
    }
}

// Parantezleri değiştirir
void swapBrackets(char* exp) {
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') {
            exp[i] = ')';
        } else if (exp[i] == ')') {
            exp[i] = '(';
        }
    }
}

// Infix'i Prefix'e dönüştür
void infixToPrefix(char* infix, char* prefix) {
    struct Stack s;
    initStack(&s);
    
    // İnfix ifadeyi ters çevir ve parantezleri değiştir
    reverse(infix);
    swapBrackets(infix);
    
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        
        // Eğer operand ise sonucu yaz
        if (isOperand(ch)) {
            prefix[k++] = ch;
        }
        // Eğer sol parantez ise yığına koy
        else if (ch == '(') {
            push(&s, ch);
        }
        // Eğer sağ parantez ise sol paranteze ulaşana kadar çıkar
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                prefix[k++] = pop(&s);
            }
            pop(&s);  // Sol parantezi çıkar
        }
        // Operatör ile karşılaşılırsa
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                prefix[k++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    // Kalan operatörleri yığından çıkar
    while (!isEmpty(&s)) {
        prefix[k++] = pop(&s);
    }
    
    prefix[k] = '\0';  // Null sonlandırıcı ekle
    
    // Sonucu ters çevir
    reverse(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];
    
    printf("Infix ifadeyi girin: ");
    scanf("%s", infix);
    
    infixToPrefix(infix, prefix);
    
    printf("Prefix ifade: %s\n", prefix);
    
    return 0;
}