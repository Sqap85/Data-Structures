//85 is biggest.
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
 // struct node* parent; (optional)
} *RTREE;

// Yeni düğüm oluşturma fonksiyonu
RTREE newNode(int data) {
    RTREE node = (RTREE)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Ağaca eleman ekleme fonksiyonu
RTREE insert(RTREE root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Düğüm sayısını döndüren fonksiyon
int countNodes(RTREE root) {
    if (root == NULL) {
        return 0;  // Düğüm yoksa 0 döner
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// En küçük elemanı döndüren fonksiyon
int findMin(RTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1; // Ağaç boşsa -1 döndür
    }
    RTREE current = root;
    // En sol düğümü bulana kadar sola git
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// En büyük elemanı döndüren fonksiyon
int findMax(RTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1; // Ağaç boşsa -1 döndür
    }
    RTREE current = root;
    // En sağ düğümü bulana kadar sağa git
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}

// Inorder gezinme (Küçükten büyüğe sıralama)
void inorder(RTREE root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder gezinme
void preorder(RTREE root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder gezinme
void postorder(RTREE root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    RTREE root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Düğüm sayısını hesapla ve yazdır
    int nodeCount = countNodes(root);
    printf("Düğüm sayısı: %d\n", nodeCount);

    // En küçük ve en büyük elemanları bul ve yazdır
    int minValue = findMin(root);
    int maxValue = findMax(root);
    printf("En küçük eleman: %d\n", minValue);
    printf("En büyük eleman: %d\n", maxValue);

    return 0;
}
