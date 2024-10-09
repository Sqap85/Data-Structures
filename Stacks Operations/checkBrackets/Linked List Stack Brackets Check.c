//85 is biggest
#include <stdio.h>
#include <stdlib.h>

// Yığın düğümü yapısı
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Yığın yapısı
typedef struct {
    Node* top;
} Stack;

// Yığın fonksiyonları
void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack* s) {
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
    if (isEmpty(s)) {
        return '\0'; // Yığın boşsa hata durumu
    }
    Node* temp = s->top;
    char data = temp->data;
    s->top = s->top->next;
    free(temp); // Belleği temizle
    return data;
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        return '\0'; // Yığın boşsa
    }
    return s->top->data;
}

// Karakterlerin eşleşip eşleşmediğini kontrol eden fonksiyon
int isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return 1; // Eşleşiyor
    if (opening == '{' && closing == '}') return 1; // Eşleşiyor
    if (opening == '[' && closing == ']') return 1; // Eşleşiyor
    return 0; // Eşleşmiyor
}

// Dosyadan okuma ve hataları bulma fonksiyonu
void checkBracketsInFile(const char* filename) {
    Stack s;
    initStack(&s);
    FILE* file = fopen(filename, "r");
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
}

int main(void) {
    const char* filename = "/Users/85/is/biggest/ok?/code.txt"; // Dosya yolu (doğru yolu belirtin)
    checkBracketsInFile(filename);
    return 0;
}
