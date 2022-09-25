#include <stdio.h>
#include <stdlib.h>

typedef struct BLG
{
    struct BLG *sonraki;
    struct BLG *onceki;
    int data;
} liste1,liste2;

liste1 * birinci_liste1, *sonuncu_liste1;
liste2 * birinci_liste2, *sonuncu_liste2;

void ekle(int hangisi, int gelen_data)
{
    if(hangisi == 1)
    {
        liste1 * temp;
        if(birinci_liste1 == NULL)
        {
            temp = (liste1 *)malloc(sizeof(liste1));
            temp->data = gelen_data;
            temp->onceki = NULL;
            temp->sonraki = NULL;
            birinci_liste1 = temp;
            sonuncu_liste1 = temp;
        }
        else
        {
            temp = (liste1 *)malloc(sizeof(liste1));
            temp->data = gelen_data;
            temp->onceki = sonuncu_liste1;
            temp->sonraki = NULL;
            sonuncu_liste1->sonraki = temp;
            sonuncu_liste1 = temp;
        }
    }
    else if(hangisi == 2)
    {
        liste2 * temp;
        if(birinci_liste2 == NULL)
        {
            temp = (liste2 *)malloc(sizeof(liste2));
            temp->data = gelen_data;
            temp->onceki = NULL;
            temp->sonraki = NULL;
            birinci_liste2 = temp;
            sonuncu_liste2 = temp;
        }
        else
        {
            temp = (liste2 *)malloc(sizeof(liste2));
            temp->data = gelen_data;
            temp->onceki = sonuncu_liste2;
            temp->sonraki = NULL;
            sonuncu_liste2->sonraki = temp;
            sonuncu_liste2 = temp;
        }
    }
}

void tek_cift_ayir()
{
    liste1 *gecici1= birinci_liste1;
    liste2 *gecici2= birinci_liste2;
    while(gecici1 != NULL)
    {
        if(gecici1->data % 2 == 0 && gecici1->onceki == NULL)
        {
            birinci_liste1 = gecici1->sonraki;
            gecici1->sonraki->onceki = NULL;
            gecici2 = gecici1;
            gecici1 = birinci_liste1;
            gecici2->onceki = sonuncu_liste2;
            gecici2->sonraki = NULL;
            sonuncu_liste2->sonraki = gecici2;
            sonuncu_liste2 = gecici2;
        }
        else if(gecici1->data % 2 == 0 && gecici1->sonraki == NULL)
        {
            sonuncu_liste1 = gecici1->onceki;
            gecici1->onceki->sonraki = NULL;
            gecici2 = gecici1;
            gecici2->onceki = sonuncu_liste2;
            gecici2->sonraki = NULL;
            sonuncu_liste2->sonraki = gecici2;
            sonuncu_liste2 = gecici2;
            break;
        }
        else if(gecici1->data % 2 == 0)
        {
            gecici1->onceki->sonraki = gecici1->sonraki;
            gecici1->sonraki->onceki = gecici1->onceki;
            gecici2 = gecici1;
            gecici1 = gecici1->sonraki;
            gecici2->onceki = sonuncu_liste2;
            gecici2->sonraki = NULL;
            sonuncu_liste2->sonraki = gecici2;
            sonuncu_liste2 = gecici2;
        }
        else
        {
            gecici1 = gecici1->sonraki;
        }
    }
    gecici2= birinci_liste2;
    while(gecici2 != NULL)
    {
        if(gecici2->data % 2 != 0 && gecici2->onceki == NULL)
        {
            birinci_liste2 = gecici2->sonraki;
            gecici2->sonraki->onceki = NULL;
            gecici1 = gecici2;
            gecici2 = birinci_liste2;
            gecici1->onceki = sonuncu_liste1;
            gecici1->sonraki = NULL;
            sonuncu_liste1->sonraki = gecici1;
            sonuncu_liste1 = gecici1;
        }
        else if(gecici2->data % 2 != 0 && gecici2->sonraki == NULL)
        {
            sonuncu_liste2 = gecici2->onceki;
            gecici2->onceki->sonraki = NULL;
            gecici1 = gecici2;
            gecici1->onceki = sonuncu_liste1;
            gecici1->sonraki = NULL;
            sonuncu_liste1->sonraki = gecici1;
            sonuncu_liste1 = gecici1;
            break;
        }
        else if(gecici2->data % 2 != 0)
        {
            gecici2->onceki->sonraki = gecici2->sonraki;
            gecici2->sonraki->onceki = gecici2->onceki;
            gecici1 = gecici2;
            gecici2 = gecici2->sonraki;
            gecici1->onceki = sonuncu_liste1;
            gecici1->sonraki = NULL;
            sonuncu_liste1->sonraki = gecici1;
            sonuncu_liste1 = gecici1;
        }
        else
        {
            gecici2 = gecici2->sonraki;
        }
    }
}

void sirala()
{
    liste1 *gecici1= birinci_liste1;
    liste2 *gecici2= birinci_liste2;
    while(gecici1->sonraki != NULL)
    {
        if(gecici1->data > gecici1->sonraki->data)
        {
            gecici1 = gecici1->sonraki;
        }
        else
        {
            if(gecici1->onceki == NULL)
            {
                gecici1->onceki = gecici1->sonraki;
                gecici1->sonraki = gecici1->sonraki->sonraki;
                gecici1->onceki->onceki = NULL;
                gecici1->onceki->sonraki = gecici1;
                gecici1->sonraki->onceki = gecici1;
                birinci_liste1 = gecici1->onceki;
            }
            else if(gecici1->sonraki->sonraki == NULL)
            {
                gecici1->onceki->sonraki =gecici1->sonraki;
                gecici1->sonraki->sonraki = gecici1;
                gecici1->sonraki->onceki = gecici1->onceki;
                gecici1->onceki = gecici1->sonraki;
                gecici1->sonraki = NULL;
                sonuncu_liste1 = gecici1;
            }
            else
            {
                liste1 *gs = gecici1->sonraki;
                gecici1->sonraki = gecici1->sonraki->sonraki;
                gs->sonraki = gecici1;
                gecici1->onceki->sonraki = gs;
                gecici1->sonraki->onceki = gecici1;
                gs->onceki = gecici1->onceki;
                gecici1->onceki = gs;
            }
            gecici1= birinci_liste1;
        }
    }
    while(gecici2->sonraki != NULL)
    {
        if(gecici2->data < gecici2->sonraki->data)
        {
            gecici2 = gecici2->sonraki;
        }
        else
        {
            if(gecici2->onceki == NULL)
            {
                gecici2->onceki = gecici2->sonraki;
                gecici2->sonraki = gecici2->sonraki->sonraki;
                gecici2->onceki->onceki = NULL;
                gecici2->onceki->sonraki = gecici2;
                gecici2->sonraki->onceki = gecici2;
                birinci_liste2 = gecici2->onceki;
            }
            else if(gecici2->sonraki->sonraki == NULL)
            {
                gecici2->onceki->sonraki =gecici2->sonraki;
                gecici2->sonraki->sonraki = gecici2;
                gecici2->sonraki->onceki = gecici2->onceki;
                gecici2->onceki = gecici2->sonraki;
                gecici2->sonraki = NULL;
                sonuncu_liste2 = gecici2;
            }
            else
            {
                liste2 *gs = gecici2->sonraki;
                gecici2->sonraki = gecici2->sonraki->sonraki;
                gs->sonraki = gecici2;
                gecici2->onceki->sonraki = gs;
                gecici2->sonraki->onceki = gecici2;
                gs->onceki = gecici2->onceki;
                gecici2->onceki = gs;
            }
            gecici2= birinci_liste2;
        }
    }
}

void birlestir()
{
    liste1 *gecici1= birinci_liste1;
    liste2 *gecici2= birinci_liste2;
    while(gecici2 != NULL)
    {
        liste2 * temp = gecici2;
        gecici2 = gecici2->sonraki;
        birinci_liste2 = gecici2;
        gecici2 = birinci_liste2;
        if(gecici1 == sonuncu_liste1)
        {
            gecici1->sonraki = temp;
            temp->onceki = gecici1;
            temp->sonraki = NULL;
            sonuncu_liste1 = temp;
            gecici1=gecici1->sonraki;
        }
        else
        {
            temp->sonraki = gecici1->sonraki;
            gecici1->sonraki->onceki= temp;
            gecici1->sonraki = temp;
            temp->onceki = gecici1;
            gecici1 = gecici1->sonraki->sonraki;
        }
    }
}

void listele()
{
    liste1 *gecici1= birinci_liste1;
    liste2 *gecici2= birinci_liste2;
    printf("liste1 = ");
    while(gecici1 != NULL)
    {
        if(gecici1==sonuncu_liste1)
            printf("%d ",gecici1->data);
        else
            printf("%d | ",gecici1->data);
        gecici1 = gecici1->sonraki;
    }
    printf("\nliste2 = ");
    while(gecici2 != NULL)
    {
        if(gecici2==sonuncu_liste2)
            printf("%d ",gecici2->data);
        else
            printf("%d | ",gecici2->data);
        gecici2 = gecici2->sonraki;
    }
    printf("\n\n");
}

int main()
{
    ekle(1,16);
    ekle(1,18);
    ekle(1,46);
    ekle(1,12);
    /*ekle(1,8);
    ekle(1,7);
    ekle(1,6);
    ekle(1,1);
    ekle(1,16);*/
    ekle(2,60);
    ekle(2,48);
    ekle(2,-6);
    ekle(2,14);
    /*ekle(2,35);
    ekle(2,3);*/
    listele();
    tek_cift_ayir();
    sirala();
    birlestir();
    listele();
    return 0;
}
