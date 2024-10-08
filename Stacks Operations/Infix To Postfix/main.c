#include <stdio.h>
#include <string.h>

#define MAX 100

// Yığın (Stack) yapısı
typedef struct {
    char data[MAX];
    int top;
} Stack;

// Yığın (Stack) başlatma fonksiyonu
void initStack(Stack *s) {
    s->top = -1;
}

// Yığının boş olup olmadığını kontrol etme
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Yığına eleman ekleme (push)
void push(Stack *s, char value) {
    if (s->top < MAX - 1) {
        s->data[++(s->top)] = value;
    }
}

// Yığından eleman çıkarma (pop)
char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0'; // Yığın boşsa
}

// Yığının tepesindeki elemanı görüntüleme (peek)
char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0'; // Yığın boşsa
}

// Operatör olup olmadığını kontrol etme
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Operatör önceliğini belirleme fonksiyonu
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Harf ya da rakam olup olmadığını kontrol etme
int isOperand(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

// Infix'ten Postfix'e dönüştürme
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        // Eğer operand ise, doğrudan postfix dizisine ekle
        if (isOperand(ch)) {
            postfix[j++] = ch;
        }
        // Eğer '(' ise, yığına ekle
        else if (ch == '(') {
            push(&s, ch);
        }
        // Eğer ')' ise, '(' bulunana kadar yığından pop yap ve postfix'e ekle
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // '(''yi de yığından çıkar
        }
        // Eğer operatörse
        else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    // Yığında kalan operatörleri postfix'e ekle
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0'; // Sonlandırıcı karakter
}

int main(void) {
    char infix[MAX], postfix[MAX];

    printf("Infix ifadeyi girin: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    return 0;
}
