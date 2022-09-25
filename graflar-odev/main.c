#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct EDGE
{
    struct EDGE* eNext;
    int weight;
    char eName[SIZE];
} edge;

typedef struct NODE
{
    char nName[SIZE];
    struct NODE* nNext;
    edge* root;
} node;

typedef struct PATH
{
    char name[SIZE];
    struct PATH* next;
    int weight;
} path;


int reach = 0;//Bagli graf sorgusu icin kullanilan global degisken


int nodeCounter(node* root)
{
    int counter = 0;
    while(root!=NULL)
    {
        counter++;
        root = root->nNext;
    }
    return counter;
}

int edgeCounter(edge* root)
{
    int counter = 0;
    while(root!=NULL)
    {
        counter++;
        root = root->eNext;
    }
    return counter;
}

int isItThere(char character[SIZE], path* pRoot)//yol struct yapisinin icinde gelen veriyi ariyan fonksiyon
{
    int available= 0;
    path* pTemp = pRoot;
    while(pTemp!=NULL)
    {
        if(strcmp(pTemp->name,character)==0)
        {
            available = 1;
            break;
        }
        pTemp = pTemp->next;
    }
    return available;
}

void display(node* root)
{
    node* temp = root;
    while(temp!=NULL)
    {
        printf("\n");
        printf("%s | ",temp->nName);
        edge* temp2 = temp->root;
        while(temp2!=NULL)
        {
            if(temp2->eNext==NULL)
                printf("%s(%d)",temp2->eName,temp2->weight);
            else
                printf("%s(%d) -> ",temp2->eName,temp2->weight);
            temp2 = temp2->eNext;
        }
        temp = temp->nNext;
    }
}

void isItCompleteGraph(node* root)
{
    node* temp = root;
    int numberOfNodes = nodeCounter(temp);
    while(temp!=NULL)
    {
        int numberOfEdges = edgeCounter(temp->root);
        if(numberOfEdges!=numberOfNodes-1)
        {
            printf("KompleGraf Degildir! %s Butun Nodelara Erisemiyor!",temp->nName);
            return;
        }
        temp = temp->nNext;
    }
    printf("Komple Graf");
}

void del(path* pRoot)//yol struct yapisindan son veriyi silme islemini yapan fonksiyon
{
    path* pTemp = pRoot;
    path* pTempPre= NULL;
    if(pTemp->next == NULL)
    {
        free(pTemp);
        pRoot =NULL;
    }
    else
    {
        while(pTemp->next!=NULL)
        {
            pTempPre = pTemp;
            pTemp = pTemp->next;
        }
        pTempPre->next =NULL;
        free(pTemp);
    }
}

void findPath(char src[SIZE], char dest[SIZE], node* root, path* pRoot,int isItQuery, int weight)
{
    node* nTemp = root;
    if(strcmp(src,dest)==0)
    {
        int totalWeight=0;
        if(isItQuery== 0)
        {
            printf("\n|");
            path* pTemp = pRoot;
            while(pTemp!=NULL)
            {
                printf("%s->",pTemp->name);
                totalWeight+=pTemp->weight;
                pTemp = pTemp->next;
            }
            printf("%s   ( %d )",dest,totalWeight+weight);
        }
        reach = 1;
    }
    else
    {
        while(nTemp!=NULL)
        {
            if(strcmp(src,nTemp->nName)==0)
            {
                path* pNew = (path*)malloc(sizeof(path));
                strcpy(pNew->name,nTemp->nName);
                pNew->next= NULL;
                pNew->weight = weight;
                if(pRoot == NULL)
                {
                    pRoot = pNew;
                }
                else
                {
                    path* pTemp = pRoot;
                    while(pTemp->next !=NULL)
                    {
                        pTemp = pTemp->next;
                    }
                    pTemp->next = pNew;
                }
                edge* eTemp = nTemp->root;
                while(eTemp!=NULL)
                {
                    if(isItThere(eTemp->eName, pRoot)!= 1)
                    {
                        findPath(eTemp->eName,dest,root,pRoot,isItQuery,eTemp->weight);
                    }
                    eTemp = eTemp->eNext;
                }
                if(pRoot!=NULL)
                    del(pRoot);
                break;
            }
            nTemp = nTemp->nNext;
        }
    }
}

void isItConnectedGraph(node* nRoot)
{
    node* temp = nRoot;
    char first[SIZE];
    strcpy(first,temp->nName);
    while(temp->nNext!=NULL)
    {
        reach = 0;
        findPath(first,temp->nName,nRoot,NULL,1,0);
        if(reach == 0)
        {
            printf("\nBagli Graf Degil! %s -> %s ulasilamiyor.\n",first,temp->nName);
            break;
        }
        temp = temp->nNext;
    }
    if(reach == 1)
    {
        printf("\nBagli Graf!\n");
        reach =0;
    }
}

int main()
{
    node* root = NULL;
    FILE *file=fopen("odev.txt","r");
    char src[SIZE],dest[SIZE],character;
    int weight;
    while(character!=EOF)
    {
        fscanf(file,"%s %s %d",&src,&dest,&weight);
        //printf("%s,%s,%d\n",src,dest,weight);
        character = fgetc(file);

        if(character=='\n' || character == EOF)
        {
            if(strcmp(src,dest)!=0)
            {
                if(root == NULL)
                {
                    node* nNew = (node*)malloc(sizeof(node));
                    nNew->nNext = NULL;
                    strcpy(nNew->nName,dest);
                    nNew->root = (edge*)malloc(sizeof(edge));
                    nNew->root->eNext=NULL;
                    strcpy(nNew->root->eName,src);
                    nNew->root->weight = weight;

                    root = (node*)malloc(sizeof(node));
                    root->nNext = nNew;
                    strcpy(root->nName,src);
                    root->root = (edge*)malloc(sizeof(edge));
                    root->root->eNext=NULL;
                    strcpy(root->root->eName,dest);
                    root->root->weight = weight;
                }
                else
                {
                    node* temp = root;
                    int isItDone = 0,isItDone2 = 0;
                    while(temp!=NULL)
                    {
                        if(strcmp(temp->nName,src)!=0 && isItDone == 0)//kaynak noktasi daha onceden yoksa true
                        {
                            if(temp->nNext==NULL)//artik bulamadiysa
                            {
                                node* nNew = (node*)malloc(sizeof(node));
                                nNew->nNext=NULL;
                                strcpy(nNew->nName,src);
                                nNew->root= (edge*)malloc(sizeof(edge));
                                nNew->root->eNext =NULL;
                                strcpy(nNew->root->eName,dest);
                                nNew->root->weight = weight;
                                temp->nNext=nNew;
                                isItDone = 1;
                            }
                        }
                        else if(isItDone == 0)
                        {
                            edge* temp2 = temp->root;
                            while(temp2!=NULL)
                            {
                                if(strcmp(temp2->eName,dest)!=0)//kaynak noktasi daha onceden var ise varis noktasi kontrolu
                                {
                                    if(temp2->eNext == NULL)
                                    {
                                        edge* eNew = (edge*)malloc(sizeof(edge));
                                        eNew->eNext =NULL;
                                        strcpy(eNew->eName,dest);
                                        eNew->weight = weight;
                                        temp2->eNext=eNew;
                                        isItDone = 1;
                                        break;
                                    }
                                }
                                else
                                {
                                    isItDone = 1;
                                    break;
                                }
                                temp2=temp2->eNext;
                            }
                        }
                        if(strcmp(temp->nName,dest)!=0 && isItDone2 == 0)//varis noktasi daha onceden yoksa true
                        {
                            if(temp->nNext==NULL)//artik bulamadiysa
                            {
                                node* nNew = (node*)malloc(sizeof(node));
                                nNew->nNext=NULL;
                                strcpy(nNew->nName,dest);
                                nNew->root = (edge*)malloc(sizeof(edge));
                                nNew->root->eNext = NULL;
                                strcpy(nNew->root->eName,src);
                                nNew->root->weight = weight;
                                temp->nNext=nNew;
                                isItDone2 = 1;
                            }
                        }
                        else if(isItDone2 == 0)
                        {
                            edge* temp2 = temp->root;
                            while(temp2!=NULL)
                            {
                                if(strcmp(temp2->eName,src)!=0)//varis noktasi daha onceden var ise kaynak noktasi kontrolu
                                {
                                    if(temp2->eNext == NULL)
                                    {
                                        edge* eNew = (edge*)malloc(sizeof(edge));
                                        eNew->eNext =NULL;
                                        strcpy(eNew->eName,src);
                                        eNew->weight = weight;
                                        temp2->eNext=eNew;
                                        isItDone2 = 1;
                                        break;
                                    }
                                }
                                else
                                {
                                    isItDone2 = 1;
                                    break;
                                }
                                temp2=temp2->eNext;
                            }
                        }
                        temp = temp->nNext;
                    }
                }
            }
        }
    }
    fclose(file);
    int exit=0;
    char source[SIZE],destination[SIZE];
    while(exit!=1)
    {
        reach = 0;
        isItCompleteGraph(root);
        isItConnectedGraph(root);
        display(root);
        printf("\n========================\n");
        printf("Kaynak Giriniz: ");
        scanf("%s",&source);
        printf("Hedef Giriniz: ");
        scanf("%s",&destination);
        printf("========================\n");
        if(strcmp(source,destination)!=0)
            findPath(source,destination,root,NULL,0,0);
        if(reach == 0)
            printf("\nYol Yok!");
        printf("\n\nCikis Yapmak Icin '1' ,Yeni Sorgu Yapmak Icin '0' Tuslayin: ");
        scanf("%d",&exit);
        system("cls");
        if(exit!=0)
            break;
    }
}
