// 85 is biggest.
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} *BTREE;

// Yeni düğüm oluşturma fonksiyonu
BTREE newNode(int data) {
    BTREE node = (BTREE)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Ağaca eleman ekleme fonksiyonu
BTREE insert(BTREE root, int data) {
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
int countNodes(BTREE root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// En küçük elemanı döndüren fonksiyon
int findMin(BTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1;
    }
    BTREE current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

// En büyük elemanı döndüren fonksiyon
int findMax(BTREE root) {
    if (root == NULL) {
        printf("Ağaç boş!\n");
        return -1;
    }
    BTREE current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->data;
}

// Ağacın yüksekliğini bulan fonksiyon
int getHeight(BTREE root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

BTREE delete_node(BTREE root, int x) {
    BTREE p, q;

    if (root == NULL) { 
        // Eğer ağaç boşsa NULL döner.
        return NULL;
    }

    if (root->data == x) {
        // 1. DURUM: Yaprak düğüm (Sol ve sağ alt ağaç yok).
        if (root->left == NULL && root->right == NULL) { 
            free(root);
            return NULL;
        } 
        // 2. DURUM: Tek çocuklu düğüm (Sadece sağ alt ağaç veya sadece sol alt ağaç var).
        else { 
            if (root->left == NULL) { 
                // Sol alt ağaç yoksa, sağ alt ağacı geri döndür.
                p = root->right;
                free(root);
                return p;
            } else if (root->right == NULL) { 
                // Sağ alt ağaç yoksa, sol alt ağacı geri döndür.
                p = root->left;
                free(root);
                return p;
            } 
            // 3. DURUM: İki çocuklu düğüm (Hem sol hem sağ alt ağaç var).
            else { 
                // Sağ alt ağacın en küçük elemanını bul ve kök yerine koy.
                p = q = root->right;
                while (p->left != NULL) { 
                    p = p->left;
                }
                // En küçük düğümü, sol alt ağacı kökün soluna bağlayarak taşır.
                p->left = root->left;
                free(root);
                return q; // Sağ alt ağacın kökünü yeni kök yapar.
            }
        }
    } 
    // Eğer silinecek düğümün değeri kökten büyükse, sağ alt ağaçta ara.
    else if (root->data < x) { 
        root->right = delete_node(root->right, x);
    } 
    // Eğer silinecek düğümün değeri kökten küçükse, sol alt ağaçta ara.
    else { 
        root->left = delete_node(root->left, x);
    }

    return root; // Güncellenmiş kökü döndür.
}
// Inorder gezinme (left-root-right)
void inorder(BTREE root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder gezinme (root-left-right)
void preorder(BTREE root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder gezinme (left-right-root)
void postorder(BTREE root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    BTREE root = NULL;

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
