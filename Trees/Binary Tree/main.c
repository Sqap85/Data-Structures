// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
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
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// En küçük elemanı döndüren fonksiyon
int findMin(RTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1;
    }
    RTREE current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// En büyük elemanı döndüren fonksiyon
int findMax(RTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1;
    }
    RTREE current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}

// Ağacın yüksekliğini bulan fonksiyon
int getHeight(RTREE root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Düğüm silme fonksiyonu
RTREE delete_node(RTREE root, int x) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == x) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->right == NULL) {
            RTREE temp = root->left;
            free(root);
            return temp;
        } else if (root->left == NULL) {
            RTREE temp = root->right;
            free(root);
            return temp;
        } else {
            RTREE temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            root->data = temp->data;
            root->left = delete_node(root->left, temp->data);
            return root;
        }
    } else if (root->data < x) {
        root->right = delete_node(root->right, x);
    } else {
        root->left = delete_node(root->left, x);
    }
    return root;
}

// Inorder gezinme (left-root-right)
void inorder(RTREE root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder gezinme (root-left-right)
void preorder(RTREE root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder gezinme (left-right-root)
void postorder(RTREE root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    RTREE root = NULL;

    // Ağaca eleman ekleme
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    insert(root, 85); // En büyük eleman

    // Inorder, Preorder, Postorder sıralamalarını yazdır
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Düğüm sayısını yazdır
    printf("Düğüm sayısı: %d\n", countNodes(root));

    // En küçük ve en büyük elemanları yazdır
    printf("En küçük eleman: %d\n", findMin(root));
    printf("En büyük eleman: %d\n", findMax(root));

    // Ağacın yüksekliğini yazdır
    printf("Ağacın yüksekliği: %d\n", getHeight(root));

    // Silme işlemi örneği
    int valueToDelete = 50;
    printf("\n%d düğümü siliniyor...\n", valueToDelete);
    root = delete_node(root, valueToDelete);

    // Silme sonrası Inorder sıralaması
    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}
