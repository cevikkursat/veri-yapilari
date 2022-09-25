#include <stdio.h>
#include <stdlib.h>

typedef struct numbers
{
    int data;
    struct numbers *Next;
} num;

num* first= NULL;
num* last;
num* temp;

void add(int data)
{
    num *iter = first;
    temp =(num*)malloc(sizeof(num));
    temp->data= data;
    temp->Next= NULL;
    last = temp;
    if(first== NULL)
    {
        first = temp;
    }
    else
    {
        while(iter->Next != NULL)
        {
            iter=iter->Next;
        }
        iter->Next=temp;
    }
}

void display()
{
    num *iter= first;
    while(iter != NULL)
    {
        printf("%d ->",iter->data);
        iter=iter->Next;
    }
}

num *reverse_turn(num *iter)
{
    if(iter->Next == NULL)
    {
        return iter;
    }
    temp = reverse_turn(iter->Next);
    if(iter->Next->Next == NULL)
    {
        last = first;
        first = iter->Next;
    }
    temp->Next = iter;
    if(last==iter)
        last->Next=NULL;
    return iter;
}
/*
int topla()
{
    if(iter->Next == NULL)
    {
        return iter->data;
    }
    int toplam= topla(iter->Next);
    return toplam+
}
*/
int main()
{
    add(12);
    add(32);
    add(34);
    add(45);
    add(56);
    add(67);
    add(1);
    add(6);
    add(89);
    display();
    reverse_turn(first);

    printf("\n");
    display();
    int sayi = topla(first,toplamm);
    printf("%d",toplamm);

}
