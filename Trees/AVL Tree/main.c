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
    node->height = 0;  // Yükseklik başlangıçta 0 olarak ayarlanır.
    return node;
}

// Düğüm yüksekliği
int height(AVLTREE* node) {
    return node ? node->height : -1;  // Boş düğüm için -1 döndürülür.
}

// Maksimum değer
int maxValue(int a, int b) {
    return (a > b) ? a : b;  // İki sayının en büyüğünü döndürür.
}

// Sağ dönüş
AVLTREE* rightRotate(AVLTREE* z) {
    AVLTREE* temp = z->left;
    z->left = temp->right;
    temp->right = z;

    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;  // Sağ dönüş sonucu döndürülür.
}

// Sol dönüş
AVLTREE* leftRotate(AVLTREE* z) {
    AVLTREE* temp = z->right;
    z->right = temp->left;
    temp->left = z;

    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;  // Sol dönüş sonucu döndürülür.
}

// Sol-Sağ dönüş
AVLTREE* leftRightRotate(AVLTREE* z) {
    z->left = leftRotate(z->left);  // Önce sol dönüş yapılır.
    return rightRotate(z);  // Sonra sağ dönüş yapılır.
}

// Sağ-Sol dönüş
AVLTREE* rightLeftRotate(AVLTREE* z) {
    z->right = rightRotate(z->right);  // Önce sağ dönüş yapılır.
    return leftRotate(z);  // Sonra sol dönüş yapılır.
}

// Balans faktörü
int getBalance(AVLTREE* node) {
    return node ? height(node->left) - height(node->right) : 0;  // Düğümün sol ve sağ yüksekliği arasındaki fark döndürülür.
}

// AVL ağacına ekleme
AVLTREE* insertToAVL(AVLTREE* tree, int data) {
    if (!tree) 
        return newNode(data);  // Ağaç boşsa yeni bir düğüm oluşturulur.

    if (data < tree->data)
        tree->left = insertToAVL(tree->left, data);  // Verilen değer solda eklenir.
    else if (data > tree->data)
        tree->right = insertToAVL(tree->right, data);  // Verilen değer sağda eklenir.
    else
        return tree;  // Aynı değeri tekrar eklemeyiz.

    tree->height = maxValue(height(tree->left), height(tree->right)) + 1;  // Yükseklik güncellenir.

    int balance = getBalance(tree);  // Düğümün balans faktörü hesaplanır.

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

    return tree;  // Düğüm dengede ise değişiklik yapılmaz.
}

// AVL ağacından minimum değer bulma
AVLTREE* minValueNode(AVLTREE* node) {
    AVLTREE* current = node;
    while (current->left != NULL)
        current = current->left;  // En sol alt düğüm bulunur.
    return current;  // En küçük değeri içeren düğüm döndürülür.
}

// AVL ağacından silme
AVLTREE* deleteNode(AVLTREE* root, int key) {
    if (!root)
        return root;  // Eğer kök boşsa, NULL döndürülür.

    if (key < root->data)
        root->left = deleteNode(root->left, key);  // Sol alt ağaçta silme işlemi yapılır.
    else if (key > root->data)
        root->right = deleteNode(root->right, key);  // Sağ alt ağaçta silme işlemi yapılır.
    else {
        if (!root->left || !root->right) {  // Tek çocuk veya hiç çocuk yoksa
            AVLTREE* temp = root->left ? root->left : root->right;  // Tek çocuk varsa bu atanır.

            if (!temp) {  // Eğer hiç çocuk yoksa
                temp = root;
                root = NULL;
            } else
                *root = *temp;  // Çocuk birleştirilir.

            free(temp);  // Geçici düğüm serbest bırakılır.
        } else {
            AVLTREE* temp = minValueNode(root->right);  // Sağ alt ağacın en küçük elemanı alınır.
            root->data = temp->data;  // Geçici değeri kök düğüme kopyalanır.
            root->right = deleteNode(root->right, temp->data);  // Sağ alt ağaçtan bu değeri sileriz.
        }
    }

    if (!root)
        return root;  // Eğer kök düğüm yoksa, NULL döndürülür.

    root->height = maxValue(height(root->left), height(root->right)) + 1;  // Yükseklik güncellenir.

    int balance = getBalance(root);  // Düğümün balans faktörü hesaplanır.

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

    return root;  // Düğüm dengede ise değişiklik yapılmaz.
}

// AVL ağacını öncelik sırasıyla yazdırma
void preOrder(AVLTREE* root) {
    if (root) {
        printf("%d ", root->data);  // Kök düğüm yazdırılır.
        preOrder(root->left);  // Sol alt ağaç yazdırılır.
        preOrder(root->right);  // Sağ alt ağaç yazdırılır.
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
    preOrder(root);  // Öncelik sırasına göre yazdırma.

    root = deleteNode(root, 20);  // 20'yi silme işlemi
    printf("\nSilme işleminden sonra AVL ağacı öncelik sırası: ");
    preOrder(root);  // Silme işleminden sonra ağacı yazdırma.

    return 0;
}
