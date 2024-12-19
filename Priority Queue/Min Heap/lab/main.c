#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

// Min-Heap Kuralları:
// Kök her zaman en küçük eleman olacak ve her çocuk ebeveyninden büyük veya eşit olmalıdır.
// Heapify algoritmasını kullanacağız.

typedef struct {
    int A[MAX_SIZE + 1]; // Dizi 1'den başlasın diye +1
    int cnt;             // Eleman sayısı
} PQueue;

// İki değeri takas etme fonksiyonu
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heap özelliklerini sağlamak için Heapify işlemi
void heapify(PQueue* q, int index) {
    int left = 2 * index;
    int right = 2 * index + 1;
    int smallest = index;

    // Sol çocuğun daha küçük olup olmadığını kontrol et
    if (left <= q->cnt && q->A[left] < q->A[smallest]) {
        smallest = left;
    }

    // Sağ çocuğun daha küçük olup olmadığını kontrol et
    if (right <= q->cnt && q->A[right] < q->A[smallest]) {
        smallest = right;
    }

    // Eğer en küçük eleman kök değilse, takas yap ve alt ağaçları heapify et
    if (smallest != index) {
        swap(&q->A[index], &q->A[smallest]);
        heapify(q, smallest);
    }
}

// Min-Heap'e dönüştürme işlemi
void buildMinHeap(PQueue* q) {
    // Last non-leaf node'dan başlayarak heapify işlemi yap
    for (int i = q->cnt / 2; i >= 1; i--) {
        heapify(q, i);
    }
}

// Priority Queue'yi yazdırma
void printPQueue(PQueue* q) {
    for (int i = 1; i <= q->cnt; i++) {
        printf("%d ", q->A[i]);
    }
    printf("\n");
}

// Rastgele dizi üretme
void generateRandomArray(PQueue* q) {
    srand(time(NULL));  // Random seed için zaman kullanıyoruz
    for (int i = 1; i <= MAX_SIZE; i++) {
        q->A[i] = rand() % 100 + 1;  // 1 ile 100 arasında rastgele sayılar
    }
    q->cnt = MAX_SIZE; // Diziye 20 eleman eklenmiş oldu
}

// Ana fonksiyon
int main() {
    PQueue q;
    
    generateRandomArray(&q);  // Rastgele dizi oluştur
    printf("Random dizi: ");
    printPQueue(&q);

    // Diziyi Min-Heap'e dönüştür
    buildMinHeap(&q);

    printf("Min-Heap'e dönüştürülmüş dizi: ");
    printPQueue(&q);

    return 0;
}
