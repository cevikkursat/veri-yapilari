#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

/*Tek yönlü baðýl liste kullanarak Ad, soyad, telno, verilerini tutulduðu
•	Kaydý baþa eklemeye yarayan ekleme fonksiyonu
•	Numaraya göre sýralama fonksiyonu
•	Soyada göre sýralama fonksiyonu
•	Listeleme fonksiyonu
Olan bir program yaz.*/

typedef struct BLG
{
    struct BLG *sonraki;
    char ad[20];
    char soyad[20];
    long long int telno;

} kisi;

kisi * birinci, *gecici;

void ekle()
{
    system("cls");
    gecici=birinci;
    if(birinci!=NULL)
    {
        birinci = (kisi *)malloc(sizeof(kisi));
        birinci->sonraki = gecici;
    }
    else
    {
        birinci = (kisi *)malloc(sizeof(kisi));
        birinci->sonraki = NULL;
    }
    printf("Eklenecek kisinin adi: ");
    scanf("%s",&birinci->ad);
    printf("Eklenecek kisinin soyadi: ");
    scanf("%s",&birinci->soyad);
    printf("Eklenecek kisinin telefon numarasi: ");
    scanf("%lld",&birinci->telno);
    printf("\nEkleme islemi tamamlandi. Menuye donmek icin bir tusa basiniz.");
    getch();
}

void numara_sirala()
{
    system("cls");
    gecici = birinci;
    kisi * gecici_once = NULL;
    kisi * gecici_sonra;
    while(gecici->sonraki != NULL)
    {
        if(gecici->telno >= gecici->sonraki->telno)
        {
            gecici_once = gecici;
            gecici = gecici->sonraki;
        }
        else
        {
            if(gecici_once == NULL)
            {
                gecici_sonra = gecici->sonraki;
                gecici->sonraki = gecici->sonraki->sonraki;
                gecici_sonra->sonraki = gecici;
                birinci = gecici_sonra;
            }
            else
            {
                gecici_once->sonraki = gecici->sonraki;
                gecici->sonraki = gecici->sonraki->sonraki;
                gecici_once->sonraki->sonraki = gecici;
            }
            gecici = birinci;
            gecici_once = NULL;
        }
    }
    printf("Siralama islemi tamamlandi. Menuye donmek icin bir tusa basiniz.");
    getch();
}

void soyad_sirala()
{
    system("cls");
    gecici = birinci;
    kisi * gecici_once = NULL;
    kisi * gecici_sonra;
    while(gecici->sonraki != NULL)
    {
        if(strcmp(gecici->soyad, gecici->sonraki->soyad)<0)
        {
            gecici_once = gecici;
            gecici = gecici->sonraki;
        }
        else
        {
            if(gecici_once == NULL)
            {
                gecici_sonra = gecici->sonraki;
                gecici->sonraki = gecici->sonraki->sonraki;
                gecici_sonra->sonraki = gecici;
                birinci = gecici_sonra;
            }
            else
            {
                gecici_once->sonraki = gecici->sonraki;
                gecici->sonraki = gecici->sonraki->sonraki;
                gecici_once->sonraki->sonraki = gecici;
            }
            gecici = birinci;
            gecici_once = NULL;
        }
    }
    printf("Siralama islemi tamamlandi. Menuye donmek icin bir tusa basiniz.");
    getch();
}

void listele()
{
    system("cls");
    printf("\t---Kayitlar---\n");
    gecici = birinci;
    while(gecici!= NULL)
    {
        printf("Ad: %s",gecici->ad);
        printf(" ||Soyad: %s",gecici->soyad);
        printf(" ||Telefon No: %lld\n",gecici->telno);
        gecici = gecici->sonraki;
    }
    getch();
}

int main()
{
    while(1)
    {
        system("cls");
        int secim;
        printf("1.Kayit Gir\n"
               "2.Numaraya Gore Sirala\n"
               "3.Soyada Gore Sirala\n"
               "4.Listele\n"
               "5.Cikis\n");
        printf("Secim: ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 1:
            ekle();
            break;
        case 2:
            numara_sirala();
            break;
        case 3:
            soyad_sirala();
            break;
        case 4:
            listele();
            break;
        case 5:
            return 0;
        default:
            printf("\nHatali Tuslama Yaptiniz. Menuye donmek icin bir tusa basiniz.");
            getch();
        }
    }
}
