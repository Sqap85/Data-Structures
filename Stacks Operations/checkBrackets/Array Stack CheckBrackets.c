//85 is biggest
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Stack yapısı
typedef struct {
    char data[MAX];
    int top;
} Stack;

// Stack fonksiyonları
void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->data[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0'; // Hata durumu, yığın boş
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0'; // Yığın boşsa
}

// Karakterlerin eşleşip eşleşmediğini kontrol eden fonksiyon
int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') {
        return 1; // Eşleşiyor
    } else if (opening == '{' && closing == '}') {
        return 1; // Eşleşiyor
    } else if (opening == '[' && closing == ']') {
        return 1; // Eşleşiyor
    } else {
        return 0; // Eşleşmiyor
    }
}

// Dosyadan okuma ve hataları bulma fonksiyonu
void checkBracketsInFile(const char *filename) {
    Stack s;
    initStack(&s);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);  // Açma karakteri yığına ekle
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) {
                printf("Hata: Fazla kapama karakteri '%c'\n", ch);
                fclose(file);
                return;
            }

            char top = pop(&s);
            if (!isMatchingPair(top, ch)) {
                printf("Hata: '%c' ile '%c' eşleşmiyor!\n", top, ch);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);

    if (!isEmpty(&s)) {
        printf("Hata: Fazla açma karakteri var!\n");
    } else {
        printf("Tüm parantezler doğru eşleşti.\n");
    }
    return;
}

int main(void) {
    const char *filename = "/../code.txt"; // Dosya yolu
    checkBracketsInFile(filename);
    return 0;
}
