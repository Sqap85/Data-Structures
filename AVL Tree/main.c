#include <stdio.h>
#include <stdlib.h>

// AVL ağacı düğüm yapısı
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} AVLTREE;

// Yeni düğüm oluşturma fonksiyonu
AVLTREE* newNode(int data) {
    AVLTREE* node = (AVLTREE*)malloc(sizeof(AVLTREE));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Düğüm yüksekliği
int height(AVLTREE* node) {
    return node ? node->height : 0;
}

// Maksimum değer
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

// Sağ dönüş
AVLTREE* rightRotate(AVLTREE* z) {
    AVLTREE* temp = z->left;
    z->left = temp->right;
    temp->right = z;

    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;
}

// Sol dönüş
AVLTREE* leftRotate(AVLTREE* z) {
    AVLTREE* temp = z->right;
    z->right = temp->left;
    temp->left = z;

    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;
}

// Sol-Sağ dönüş
AVLTREE* leftRightRotate(AVLTREE* z) {
    z->left = leftRotate(z->left);
    return rightRotate(z);
}

// Sağ-Sol dönüş
AVLTREE* rightLeftRotate(AVLTREE* z) {
    z->right = rightRotate(z->right);
    return leftRotate(z);
}

// Balans faktörü
int getBalance(AVLTREE* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// AVL ağacına ekleme
AVLTREE* insertToAVL(AVLTREE* tree, int data) {
    if (!tree) 
        return newNode(data);

    if (data < tree->data)
        tree->left = insertToAVL(tree->left, data);
    else if (data > tree->data)
        tree->right = insertToAVL(tree->right, data);
    else
        return tree;

    tree->height = maxValue(height(tree->left), height(tree->right)) + 1;

    int balance = getBalance(tree);

    // Sol-Sol durumu
    if (balance > 1 && data < tree->left->data)
        return rightRotate(tree);

    // Sağ-Sağ durumu
    if (balance < -1 && data > tree->right->data)
        return leftRotate(tree);

    // Sol-Sağ durumu
    if (balance > 1 && data > tree->left->data)
        return leftRightRotate(tree);

    // Sağ-Sol durumu
    if (balance < -1 && data < tree->right->data)
        return rightLeftRotate(tree);

    return tree;
}

// AVL ağacından minimum değer bulma
AVLTREE* minValueNode(AVLTREE* node) {
    AVLTREE* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// AVL ağacından silme
AVLTREE* deleteNode(AVLTREE* root, int key) {
    if (!root)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLTREE* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            AVLTREE* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (!root)
        return root;

    root->height = maxValue(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root);

    // Sol-Sol durumu
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Sol-Sağ durumu
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Sağ-Sağ durumu
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Sağ-Sol durumu
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// AVL ağacını öncelik sırasıyla yazdırma
void preOrder(AVLTREE* root) {
    if (root) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Ana fonksiyon
int main() {
    AVLTREE* root = NULL;

    root = insertToAVL(root, 10);
    root = insertToAVL(root, 20);
    root = insertToAVL(root, 30);
    root = insertToAVL(root, 40);
    root = insertToAVL(root, 50);
    root = insertToAVL(root, 25);

    printf("AVL ağacı öncelik sırası: ");
    preOrder(root);

    root = deleteNode(root, 20);
    printf("\nSilme işleminden sonra AVL ağacı öncelik sırası: ");
    preOrder(root);

    return 0;
}