#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Yığına eleman ekleme
void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}

// Yığından eleman çıkarma
char pop(void) {
    if (top != -1) {
        return stack[top--];
    }
    return '\0'; // Yığın boşsa
}

// Yığının en üstündeki elemanı görmek
char peek(void) {
    if (top != -1) {
        return stack[top];
    }
    return '\0'; // Yığın boşsa
}

// Operatör önceliği
int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

// İnfix ifadeyi prefix ifadeye dönüştürme
void infixToPrefix(char* infix, char* prefix) {
     int length = strlen(infix);
    char reversed[MAX];
    char result[MAX];
    int j = 0;

    // İnfix ifadeyi ters çevirme
    for (int i = 0; i < length; i++) {
        if (infix[length - 1 - i] == '(') {
            reversed[i] = ')';
        } else if (infix[length - 1 - i] == ')') {
            reversed[i] = '(';
        } else {
            reversed[i] = infix[length - 1 - i];
        }
    }
    reversed[length] = '\0';

    // Ters çevrilmiş infix ifadesini işleme
    for (int i = 0; i < length; i++) {
        char c = reversed[i];

        // Operatör değilse sonucu ekle
        if (isalnum(c)) {
            result[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(') {
                result[j++] = pop();
            }
            pop(); // '(' elemanını çıkar
        } else {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                result[j++] = pop();
            }
            push(c);
        }
    }

    // Kalan operatörleri ekle
    while (top != -1) {
        result[j++] = pop();
    }

    result[j] = '\0';

    // Sonucu ters çevir
    for (int i = 0; i < j; i++) {
        prefix[i] = result[j - 1 - i];
    }
    prefix[j] = '\0';
}

int main(void) {
    char infix[MAX], prefix[MAX];

    printf("Infix ifade girin: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix ifade: %s\n", prefix);

    return 0;
}
