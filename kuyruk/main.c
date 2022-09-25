#include <stdio.h>
#include <stdlib.h>

typedef struct siparis
{
    struct siparis * sonraki;
    int siparisNo;
    int fiyat;
    int siradaOtelemeSayac;
} siparisler;

siparisler * bas = NULL;
siparisler * son = NULL;
int siparisSayisi = 0;

void siparisEkle()
{
    siparisSayisi++;
    int ortayaMi = 0;
    int siparisTutari;
    printf("Siparis tutarini giriniz: ");
    scanf("%d",&siparisTutari);
    if(bas == NULL)
    {
        bas = (siparisler*)malloc(sizeof(siparisler));
        bas->siparisNo = siparisSayisi;
        bas->fiyat = siparisTutari;
        bas->siradaOtelemeSayac = 0;
        bas->sonraki = NULL;
        son = bas;
    }
    else
    {
        siparisler *temp = bas;
        siparisler *gecici;
        siparisler *sonraEkle;
        gecici = (siparisler*)malloc(sizeof(siparisler));
        gecici->siparisNo = siparisSayisi;
        gecici->fiyat = siparisTutari;
        gecici->siradaOtelemeSayac = 0;
        while(temp != NULL)
        {
            if(temp->fiyat<gecici->fiyat)
            {
                sonraEkle = temp;
                temp->siradaOtelemeSayac++;
                temp=temp->sonraki;
                ortayaMi = 1;
            }
            else
            {
                if(ortayaMi == 0)
                {
                    gecici->sonraki = bas;
                    bas = gecici;
                    ortayaMi = 0;
                }
                else
                {
                    sonraEkle->sonraki = gecici;
                    gecici->sonraki = temp;
                    ortayaMi = 0;
                }
                break;
            }
        }
        if(ortayaMi == 1)
        {
            sonraEkle->sonraki = gecici;
            gecici->sonraki = NULL;
            son = gecici;
        }
    }
}

void siparisiAl()
{
    if(bas!=NULL)
    {
        siparisler *cikacakdanOnce =  NULL;
        siparisler *temp = bas;
        siparisler *cikacak = son;
        while(temp != NULL)
        {
            if(temp->siradaOtelemeSayac >= 3)
            {
                if(temp->siradaOtelemeSayac >= cikacak->siradaOtelemeSayac)
                {
                    cikacak = temp;
                }
            }
            temp = temp->sonraki;
        }
        temp = bas;
        while(temp != NULL)
        {
            if(temp == cikacak)
            {
                break;
            }
            cikacakdanOnce = temp;
            temp =temp->sonraki;
        }
        if(cikacak == bas)
        {
            bas = cikacak->sonraki;
        }
        else if(cikacak == son)
        {
            cikacakdanOnce->sonraki = NULL;
            son = cikacakdanOnce;
        }
        else
        {
            cikacakdanOnce->sonraki = cikacak->sonraki;
        }
        free(cikacak);
    }
}

void siparisleriGoster()
{
    siparisler *temp = bas;
    printf("--------------------------------------Siparis Ekrani--------------------------------------------\n");
    while(temp != NULL)
    {
        printf("Siparisi No: %d\tSiparis Tutari: %d\tSiparis Oteleme Sayisi: %d\n",temp->siparisNo,temp->fiyat,temp->siradaOtelemeSayac);
        temp=temp->sonraki;
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

int main()
{
    int cikis;
    int secim;
    char hangisi;
    while(1)
    {
        system("cls");
        siparisleriGoster();
        printf("1-Siparis Ekle\n2-Siparisi Siradan Al\n3-Cikis\nSecim: ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            siparisEkle();
            break;
        case 2:
            siparisiAl();
            break;
        case 3:
            return 0;
        default:
            printf("Yanlis Tuslama Yaptiniz! Tekrar Secmek Icin 'T' Cikmak Icin 'C' Tuslayiniz: ");
            scanf(" %c",&hangisi);
            if(hangisi == 'c' || hangisi == 'C')
            {
                return 0;
            }
            else if(hangisi == 't' || hangisi == 'T')
            {
            }
            else
            {
                printf("Farkli Tuslama Algilandi Menuye Donmek Icin Bir Tusa Basiniz...\n");
                getch();
            }
            break;
        }
    }
}
