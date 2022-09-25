#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BLG
{
    struct BLG *sonraki;
    char data;
} yigin;
typedef struct BLGs
{
    struct BLGs *next;
    int datasayi;
} sonuc_yigin;

sonuc_yigin *baslangic = NULL;
yigin * bas = NULL;
char infix[100];
char postfix[100];
int sayac=1;

void push(char gelen, int gelensayi, int hangisi)
{
    if(hangisi == 1)
    {
        yigin * temp;
        temp = (yigin *)malloc(sizeof(yigin));
        temp->data= gelen;
        temp->sonraki = bas;
        bas = temp;
    }
    else
    {
        sonuc_yigin * temp;
        temp = (sonuc_yigin*)malloc(sizeof(sonuc_yigin));
        temp->datasayi= gelensayi;
        temp->next = baslangic;
        baslangic = temp;
    }
}

void pop(int hangisi)
{
    if(hangisi == 1)
    {

        yigin *temp;
        temp = bas;
        bas = bas->sonraki;
        free(temp);
    }
    else
    {
        sonuc_yigin *temp;
        temp = baslangic;
        baslangic = baslangic->next;
        free(temp);
    }
}

void yazdir(int hangisi)
{
    if(hangisi == 1)
    {
        int kac_kere = sayac;
        while(kac_kere<strlen(infix))
        {
            printf("%c",infix[kac_kere]);
            kac_kere++;
        }
        sayac++;
        yigin *temp= bas;
        if(bas==NULL)
            printf("\t\t\t  ");
        else
        {
            printf("\t\t\t");
            while(temp !=NULL)
            {
                printf("%c ",temp->data);
                temp=temp->sonraki;
            }
        }
        printf("\t\t\t%s \n",postfix);
    }
    else if (hangisi == 2)
    {
        sonuc_yigin *temp= baslangic;
        if(baslangic==NULL)
            printf("  ");
        else
        {
            while(temp !=NULL)
            {
                printf("%d ",temp->datasayi);
                temp=temp->next;
            }
        }
        printf("\n");
    }
}

int yigin_deger(char karakter, int yigin_neresi)
{
    switch(karakter)
    {
    case '^':
        if(yigin_neresi == 1)
            return 3;
        else
            return 4;
    case '*':
        if(yigin_neresi == 1)
            return 2;
        else
            return 2;
    case '/':
        if(yigin_neresi == 1)
            return 2;
        else
            return 2;
    case '+':
        if(yigin_neresi == 1)
            return 1;
        else
            return 1;
    case '-':
        if(yigin_neresi == 1)
            return 1;
        else
            return 1;
    case '(':
        if(yigin_neresi == 1)
            return 0;
        else
            return 4;
    }
}

int main()
{
    int postfix_indis = 0;
    int parantezden_sonra = 0;
    char karakter;
    printf("Infix Bir Ifade Giriniz: ");
    scanf("%s",&infix);
    for(int i = 0; i<strlen(infix); i++)
    {
        if(infix[i] == ')' || infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(')
        {
            if(infix[i] == ')')
            {
                while(bas->data != '(')
                {
                    postfix[postfix_indis] = bas->data;
                    postfix_indis++;
                    pop(1);
                }
                pop(1);
            }
            else
            {
                if(bas == NULL)
                {
                    push(infix[i],0,1);
                }
                else
                {
                    if(yigin_deger(infix[i],2) > yigin_deger(bas->data,1))
                    {
                        push(infix[i],0,1);
                    }
                    else
                    {
                        postfix[postfix_indis] = bas->data;
                        postfix_indis++;
                        pop(1);
                        i--;
                    }
                }
            }
        }
        else
        {
            postfix[postfix_indis] = infix[i];
            postfix_indis++;
        }
        yazdir(1);
    }
    while(bas !=NULL)
    {
        postfix[postfix_indis] = bas->data;
        postfix_indis++;
        pop(1);
    }
    printf("\nPostfix: %s\n\n",postfix);
    int sonuc = 0;
    for(int i = 0; i<strlen(postfix); i++)
    {
        if(postfix[i] == '^')
        {
            sonuc = 1;
            for(int i = 0; i < baslangic->datasayi; i++)
            {
                sonuc = sonuc*(int)baslangic->next->datasayi;
            }
            pop(2);
            pop(2);
            push(' ',sonuc,2);
        }
        else if(postfix[i] == '*' )
        {
            sonuc = baslangic->next->datasayi*baslangic->datasayi;
            pop(2);
            pop(2);
            push(' ',sonuc,2);
        }
        else if(postfix[i] == '/' )
        {
            sonuc = baslangic->next->datasayi/baslangic->datasayi;
            pop(2);
            pop(2);
            push(' ',sonuc,2);
        }
        else if(postfix[i] == '+')
        {
            sonuc = baslangic->next->datasayi+baslangic->datasayi;
            pop(2);
            pop(2);
            push(' ',sonuc,2);
        }
        else if(postfix[i] == '-')
        {
            sonuc = baslangic->next->datasayi-baslangic->datasayi;
            pop(2);
            pop(2);
            push(' ',sonuc,2);
        }
        else
        {
            int sayi = 0;
            sayi = postfix[i]- '0'; // char dan integer tioe casting islemi
            push(' ',sayi,2);
        }
        yazdir(2);
    }
    printf("Sonuc: %d",sonuc);
}
