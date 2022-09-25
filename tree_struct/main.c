#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOYUT 50

typedef struct agac
{
    char dosyaIsmi[BOYUT];
    int tabSayisi;
    struct agac *cocuk;
    struct agac *kardes;
} yaprak;

typedef struct konum
{
    char veri[BOYUT];
    int tab_sayisi;
    struct konum* sonraki;
} yol;

typedef struct bulunanlarinAdresleri
{
    struct bulunanlarinAdresleri *adresi;
    struct bulunanlarinAdresleri *sonraki;
} bAdresleri;

yol *bas=NULL;
yol *son=NULL;
bAdresleri *ilk=NULL;
bAdresleri *sson=NULL;
int bulunduMu=0;
int bulunaninTabSayisi;
int kactaneSayac=0;

yaprak *yaprakEkle(yaprak *root,char veri[],int gelenTabSayisi)//agac struct yapisina ekleme yaptigimiz fonksiyon
{
    if(root==NULL)
    {
        root=(yaprak*)malloc(sizeof(yaprak));
        root->cocuk=NULL;
        root->kardes=NULL;
        root->tabSayisi=gelenTabSayisi;
        strcpy(root->dosyaIsmi,veri);
        return root;
    }
    else
    {
        if(gelenTabSayisi==root->tabSayisi+1)
        {
            if(root->kardes!=NULL)
                yaprakEkle(root->kardes,veri,gelenTabSayisi);
            else
                root->cocuk=yaprakEkle(root->cocuk,veri,gelenTabSayisi);
        }
        else if(gelenTabSayisi==root->tabSayisi)
        {
            root->kardes=yaprakEkle(root->kardes,veri,gelenTabSayisi);
        }
        else
        {
            if(root->kardes!=NULL)
                yaprakEkle(root->kardes,veri,gelenTabSayisi);
            else
                yaprakEkle(root->cocuk,veri,gelenTabSayisi);
        }
    }
}

void aramaKactaneVar(yaprak *root,char aranan[])//agac yapisinin butun elemanlarýný dolaþýp aranan dosya ismini bulduðunda bulunan dosyanin adresini bulunanlarinAdresleri struct yapisinin icine attiðimiz fonksiyon
{
    if(root!=NULL)
    {
        if((strcmp(root->dosyaIsmi,aranan))==0)
        {
            kactaneSayac++;
            bAdresleri *temp = (bAdresleri*)malloc(sizeof(bAdresleri));
            temp->adresi=root;
            temp->sonraki=NULL;
            if(ilk==NULL)
            {
                ilk=temp;
                sson = temp;
            }
            else
            {
                sson->sonraki=temp;
                sson=temp;
            }
        }
        aramaKactaneVar(root->cocuk,aranan);
        aramaKactaneVar(root->kardes,aranan);
    }
}

void aramaAdresiBul(yaprak *root,char aranan[],bAdresleri * adres)//konum struct yapisinin icine ekleme yaptigimiz fonksiyon
{
    if(root!=NULL)
    {
        if(root!=adres)
        {
            if(bulunduMu==0)
            {
                yol* temp=(yol*)malloc(sizeof(yol));
                strcpy(temp->veri,root->dosyaIsmi);
                temp->tab_sayisi=root->tabSayisi;
                temp->sonraki=NULL;
                if(bas==NULL)
                {
                    bas=temp;
                    son=temp;
                }
                else
                {
                    son->sonraki=temp;
                    son=temp;
                }
            }
            aramaAdresiBul(root->cocuk,aranan,adres);
            aramaAdresiBul(root->kardes,aranan,adres);
        }
        else
        {
            bulunduMu=1;
            bulunaninTabSayisi=root->tabSayisi;
            yol* temp=(yol*)malloc(sizeof(yol));
            temp->tab_sayisi=root->tabSayisi;
            strcpy(temp->veri,root->dosyaIsmi);
            temp->sonraki=NULL;
            if(bas==NULL)
            {
                bas=temp;
                son=temp;
            }
            else
            {
                son->sonraki=temp;
                son=temp;
            }
        }
    }
}

void bulunanAdresiYazdir()//Konum struct yapisinin icine attigimiz yolu istedigimiz sekilde yazmamizi saglayan fonksiyon
{
    char dIsmi[BOYUT];
    yol* temp = bas;
    printf("%s/",temp->veri);
    for(int i=1; i<=bulunaninTabSayisi;)
    {
        if(i==temp->tab_sayisi)
        {
            strcpy(dIsmi,temp->veri);
        }
        temp=temp->sonraki;
        if(temp==NULL)
        {
            i++;
            temp=bas;
            printf("%s/",dIsmi);
        }
    }
}

void temizle(int hangisi)//Konum struct yapisini veya bulunanlarinAdresleri struct yapisini temizleyen fonksiyon
{
    bulunduMu=0;
    while(1)
    {
        if(hangisi==1)
        {
            yol *temp = bas;
            if(bas==son)
            {
                free(bas);
                bas=NULL;
                son=NULL;
                break;
            }
            while(temp->sonraki->sonraki!=NULL)
            {
                temp=temp->sonraki;
            }
            free(temp->sonraki);
            temp->sonraki=NULL;
            son=temp;
        }
        else
        {
            kactaneSayac=0;
            bAdresleri *temp = ilk;
            if(ilk==sson)
            {
                free(ilk);
                ilk=NULL;
                sson=NULL;
                break;
            }
            while(temp->sonraki->sonraki!=NULL)
            {
                temp=temp->sonraki;
            }
            free(temp->sonraki);
            temp->sonraki=NULL;
            sson=temp;
        }
    }
}

int main()
{
    char aranan[BOYUT];
    yaprak *kok=NULL;
    FILE *dosya=fopen("odev.txt","r");//agac yapisini ekrana yazdirmak icin kullandigimiz dosya
    FILE *dosya2=fopen("odev.txt","r");//agac dosya yapisini dosyadan okuyup agac struct yapisina eklemek icin kullanilan dosya
    char karakter;
    char ad[BOYUT];
    int tabSayac=0;
    int ilkKarakterMi=0;
    fscanf(dosya2,"%s",ad);
    kok = yaprakEkle(kok,ad,0);
    while(karakter!=EOF)
    {
        karakter = fgetc(dosya);
        printf("%c",karakter);
        if(karakter=='\t')
        {
            tabSayac++;
        }
        else if(karakter=='\n')
        {
            tabSayac=0;
            ilkKarakterMi=1;
        }
        else
        {
            if(ilkKarakterMi)
            {
                ilkKarakterMi=0;
                fscanf(dosya2,"%s",ad);
                yaprakEkle(kok,ad,tabSayac);
            }
        }
    }
    fclose(dosya2);
    fclose(dosya);
    printf("\n\n");
    while(1)
    {
        printf("Aramak Istediginiz Dosya Adini Giriniz (Cikmak Icin Cikis Yaziniz): ");
        scanf("%s",&aranan);
        if(strcmp(aranan,"Cikis")==0)
            break;
        aramaKactaneVar(kok,aranan);
        bAdresleri *temp=ilk;
        if(kactaneSayac!=0)
        {
            printf("%d Tane Var: ",kactaneSayac);
        }
        else
        {
            printf("Aranan Dosya Bulunamadi!");
        }
        for(int i=0; i<kactaneSayac; i++)
        {
            aramaAdresiBul(kok,aranan,temp->adresi);
            bulunanAdresiYazdir();
            temizle(1);
            if((i+1)<kactaneSayac)
            {
                printf(" - ");
                temp=temp->sonraki;
            }
        }
        temizle(0);
        printf("\n\n");
    }
}
