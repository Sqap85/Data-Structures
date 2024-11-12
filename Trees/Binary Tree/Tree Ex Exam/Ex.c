#include <stdio.h>
#include <stdlib.h>
#define Max 100

// Binary Tree (BTREE) yapısının tanımı
typedef struct BTREE {
    int data;  // Düğümde int veri
    struct BTREE *left;
    struct BTREE *right;
} BTREE;

// Stack yapısının tanımı (int türü için)
typedef struct Stack {
    int data[Max];  // 100 elemanlı dizi, int türünde
    int top;
    int counter;  // Stack'teki eleman sayısını tutan counter
} Stack;


// Stack'in dolu olup olmadığını kontrol eden fonksiyon
int isFull(Stack *s) {
    return s->counter == Max;  // Stack'teki eleman sayısı Max ise doludur
}

// Stack'in boş olup olmadığını kontrol eden fonksiyon
int isEmpty(Stack *s) {
    return s->counter == 0;  // Stack'teki eleman sayısı 0 ise boştur
}

// Stack'e eleman ekleyen fonksiyon
void push(Stack *s, int value) {
    if (isFull(s)) {  // Eğer stack doluysa, isFull ile kontrol et
        printf("Stack is full!\n");
    } else {
        s->data[s->top++] = value;  // Elemanı stack'e ekle
        s->counter++;               // Counter'ı artır
    }
}
// Yeni bir düğüm oluşturma
BTREE* newNode(int data) {
    BTREE* node = (BTREE*)malloc(sizeof(BTREE));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Her seviyedeki düğüm değerlerini toplayan fonksiyon
int levelSum(BTREE *root, int level) {
    if (root == NULL) {
        return 0;
    }
    if (level == 0) {
        return root->data;  // Direk int değeri döndürüyoruz
    } else {
        return levelSum(root->left, level - 1) + levelSum(root->right, level - 1);
    }
}

// Ağacın yüksekliğini bulma
int height(BTREE *root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Her seviyedeki toplamları stack'e ekleyen fonksiyon
Stack sumLevelToStack(BTREE *root, Stack s) {
    int h = height(root);  // Ağacın yüksekliği
    for (int i = 0; i <= h; i++) {
        int sum = levelSum(root, i);
        push(&s, sum);  // int değeri stack'e ekle
    }
    return s;  // Stack'i döndürüyoruz
}

// Stack'in içeriğini yazdıran fonksiyon
void printStack(Stack s) {
    if (isEmpty(&s)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = 0; i < s.top; i++) {  // stack'teki elemanları top'a kadar yazdır
        printf("%d ", s.data[i]);
    }
    printf("\n");
}

int main() {
    // Ağaç oluşturma
    BTREE* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    // Stack önceden başlatıldı
    Stack s;
    s.top = 0;
    s.counter = 0;  // Stack başlangıçta boş

    // Her seviyedeki toplamları stack'e ekleyin
    s = sumLevelToStack(root, s);
    
    // Stack'in içeriğini yazdırma
    printStack(s);

    return 0;
}
