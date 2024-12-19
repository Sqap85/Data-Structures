//
//  main.c
//  pd final soru
// Öğrencilerin notlarını içeren aşağıdaki tabloya sahip olduğunuzu varsayın. Her öğrencinin ortalamasını hesaplayan ve sonucu ortalama sütununa (satır indeks 4) kaydeden bir C programı yazın. Ardından, en yüksek ortalamayı alan öğrenciyi (kimlik ve ortalama) yazdırın. 2 boyutlu diziyi aşağıdaki tabloyu kullanarak ilk eğer ataması yapın (sütun başlıkları dahil olmayacak).

//  Created by Engin Elibol on 02/01/2024.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {

    int a[4][5],i,j,top,ort,max=0,maxsa;
    
    
    for (i=0; i<4; i++) {
        j=0; top=0; ort=0;
            
            printf("ID:");
            scanf("%d",&a[i][j]);
            j++;
            printf("mat notu:");
            scanf("%d",&a[i][j]);
        top+=a[i][j]; j++;
            printf("fizik notu:");
            scanf("%d",&a[i][j]);
        top+=a[i][j];  j++;
            printf("kimya notu:");
            scanf("%d",&a[i][j]);
        top+=a[i][j];
        j++;
        
        ort=top/3;
        a[i][j]=ort;
        
    }
    
    for (i=0; i<4; i++) {
        j=4;
        
        if(a[i][j]>max){max=a[i][j]; maxsa=i;}
        
        
    }

  printf("en yuksek ortalamasi olan ogrencinin id si=%d\n",a[maxsa][0]);
    printf("ortalamasi=%d\n",a[maxsa][4]);

    


    return 0;
}
