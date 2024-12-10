#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

/*
Min-Heap Kuralları:
1) Çocuklar Root'tan Büyük Olmak Zorunda
2) Her Seviye Tamamen Dolu Olmalıdır (Tam İkili Ağaç)
3) Son Seviyede Düğümler Soldan Sağa Dolu Olmalıdır

parent(i)= i/2
left(i) = 2*i
right(i) = 2*i+1

not:Kök (Root) Her Zaman En Küçük Elemandır

Min-Heap Temsili:
Ağaç yapısının dizi biçimindeki karşılığı şu şekilde olabilir:

    [2, 5, 10, 30, 20, 50]

Bu diziyi bir ikili ağaç şeklinde görselleştirelim:

          2
         / \
        5   10
       / \  / \
      30 20 50

Dizideki elemanlar, Min-Heap kurallarına uygun olarak sıralanmıştır:
- Kök her zaman en küçük eleman olan 2'yi tutar.
- Her çocuk, ebeveyninden büyük veya eşittir.
- Ağaç tam ikili bir yapıya sahiptir ve son seviyedeki düğümler soldan sağa doğru sıralanmıştır.

Dizi formundaki temsili şu şekilde daha açık gösterebiliriz:

Dizi: [2, 5, 10, 30, 20, 50]

- A[1] → 2 (kök, en küçük eleman)
- A[2] → 5 (sol çocuk)
- A[3] → 10 (sağ çocuk)
- A[4] → 30 (sol alt çocuk)
- A[5] → 20 (sağ alt çocuk)
- A[6] → 50 (sağ alt çocuk)

Hesaplamalar:
- A[1] kök olduğu için ebeveyni yoktur, ancak:
  parent(1) = 1 / 2 = 0 (geçersiz, kök)
- A[2]'nin ebeveyni:
  parent(2) = 2 / 2 = 1 (A[1] → 2)
  A[2] için sol çocuk: left(2) = 2 * 2 = 4 (A[4] → 30)
  A[2] için sağ çocuk: right(2) = 2 * 2 + 1 = 5 (A[5] → 20)
- A[3]'ün ebeveyni:
  parent(3) = 3 / 2 = 1 (A[1] → 2)
  A[3] için sol çocuk: left(3) = 2 * 3 = 6 (A[6] → 50)
  A[3] için sağ çocuk yoktur çünkü A[7] yok.

 */
typedef struct {
    int A[MAX_SIZE + 1]; // Dizi 1'den başlasın diye +1
    int cnt;             // Eleman sayısı
} PQueue;

// Priority Queue'yi başlatma
void init(PQueue* q) {
    q->cnt = 0;
}

// İki değeri takas etme fonksiyonu
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert işlemi (değer ekleme)
void insert(PQueue* q, int x) {
    if (q->cnt >= MAX_SIZE) {
        printf("Priority Queue dolu!\n");
        return;
    }

    // Değeri en sona ekle
    q->A[++q->cnt] = x;
    int index = q->cnt;

    // Percolate up
    while (index != 1 && q->A[index] < q->A[index / 2]) {
        swap(&q->A[index], &q->A[index / 2]);
        index /= 2;
    }
}

// Delete işlemi
int delete(PQueue* q) {
    if (q->cnt == 0) { // Eğer kuyruğun elemanı yoksa
        printf("Priority Queue boş!\n");
        return -1;
    }

    int min = q->A[1]; // Kök elemanı sakla (en küçük)
    q->A[1] = q->A[q->cnt--]; // Son elemanı köke taşı ve eleman sayısını azalt
    int index = 1;

    // Percolate down
    while (2 * index <= q->cnt && 
           (q->A[index] > q->A[2 * index] || (2 * index + 1 <= q->cnt && q->A[index] > q->A[2 * index + 1]))) {

        if (2 * index + 1 > q->cnt || q->A[2 * index] < q->A[2 * index + 1]) {
            swap(&q->A[index], &q->A[2 * index]); // Sol çocukla yer değiştir
            index = 2 * index;
        } else {
            swap(&q->A[index], &q->A[2 * index + 1]); // Sağ çocukla yer değiştir
            index = 2 * index + 1;
        }
    }

    return min; // En küçük elemanı döndür
}

// Priority Queue'nin Min-Heap olup olmadığını kontrol et
bool isMinHeap(PQueue* q) {
    for (int i = 1; i <= q->cnt / 2; i++) { // Sadece iç düğümleri kontrol et
        int left = 2 * i;
        int right = 2 * i + 1;

        // Sol çocuğu kontrol et
        if (left <= q->cnt && q->A[i] > q->A[left]) {
            return false;
        }

        // Sağ çocuğu kontrol et
        if (right <= q->cnt && q->A[i] > q->A[right]) {
            return false;
        }
    }
    return true;
}

// Priority Queue'yi yazdırma
void printPQueue(PQueue* q) {
    for (int i = 1; i <= q->cnt; i++) { // İndeks 1'den başlıyor
        printf("%d ", q->A[i]);
    }
    printf("\n");
}

// Ana fonksiyon
int main() {
    PQueue q;
    init(&q);

    insert(&q, 10);
    insert(&q, 5);
    insert(&q, 30);
    insert(&q, 2);

    printf("Priority Queue: ");
    printPQueue(&q);

    if (isMinHeap(&q)) {
        printf("Bu bir Min-Heap.\n");
    } else {
        printf("Bu bir Min-Heap değil.\n");
    }

    printf("Deleted: %d\n", delete(&q));
    printf("Priority Queue after delete: ");
    printPQueue(&q);

    if (isMinHeap(&q)) {
        printf("Bu bir Min-Heap.\n");
    } else {
        printf("Bu bir Min-Heap değil.\n");
    }

    return 0;
}
