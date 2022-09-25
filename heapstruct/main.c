#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* leftChild;
    struct Node* rightChild;
    struct Node* parent;
    int index;
} node;

node* root=NULL;
int isItEnd=0;
int i=1;

node* createLeaf(int pData)
{
    node* temp;
    temp=(node*)malloc(sizeof(node));
    temp->data=pData;
    temp->leftChild=NULL;
    temp->rightChild=NULL;
    temp->parent=NULL;
    temp->index=nodeCounter(root)+1;
    return temp;
}

int nodeCounter(node*leaf)
{
    if(leaf==NULL)
    {
        return 0;
    }
    return (nodeCounter(leaf->leftChild)+nodeCounter(leaf->rightChild))+1;
}

void insertLeaf(node* leaf,node* temp)
{
    if(root==NULL)
    {
        root=temp;
    }
    else
    {
        if(leaf!=NULL)
        {
            if(leaf->index==(temp->index/2))
            {
                temp->parent=leaf;
                if(temp->index==leaf->index*2)
                {
                    leaf->leftChild=temp;
                }
                else
                {
                    leaf->rightChild=temp;
                }
            }
            insertLeaf(leaf->leftChild,temp);
            insertLeaf(leaf->rightChild,temp);
        }
    }
}

void afterInsert(node* leaf,int lastIndex)
{
    if(leaf!=NULL)
    {
        if(leaf->index==lastIndex)
        {
            while(isItEnd==0)
            {
                if(leaf->parent!=NULL)
                {
                    if(leaf->data>leaf->parent->data)
                    {
                        node* temp_leftChild=leaf->leftChild;
                        node* temp_rightChild=leaf->rightChild;
                        int temp_index= leaf->index;
                        node* temp_parent= leaf->parent;
                        if(leaf->index==(leaf->parent->index*2))
                        {
                            leaf->rightChild=leaf->parent->rightChild;
                            if(leaf->rightChild!=NULL)
                                leaf->rightChild->parent=leaf;
                            leaf->leftChild=leaf->parent;

                        }
                        else
                        {
                            leaf->leftChild=leaf->parent->leftChild;
                            if(leaf->leftChild!=NULL)
                                leaf->leftChild->parent=leaf;
                            leaf->rightChild=leaf->parent;
                        }
                        leaf->parent->leftChild=temp_leftChild;
                        leaf->parent->rightChild=temp_rightChild;
                        leaf->index=leaf->parent->index;
                        leaf->parent->index=temp_index;
                        leaf->parent=leaf->parent->parent;
                        temp_parent->parent=leaf;
                        if(temp_leftChild!=NULL)
                            temp_leftChild->parent=temp_parent;
                        if(temp_rightChild!=NULL)
                            temp_rightChild->parent=temp_parent;
                        if(leaf->parent!=NULL)
                        {
                            if(leaf->index==(leaf->parent->index*2))
                            {
                                leaf->parent->leftChild=leaf;
                            }
                            else
                            {
                                leaf->parent->rightChild=leaf;
                            }
                        }
                        if(leaf->index==1)
                        {
                            root=leaf;
                            isItEnd=1;
                        }
                    }
                    else
                        isItEnd=1;
                }
                else
                    isItEnd=1;
            }
        }
        afterInsert(leaf->leftChild,lastIndex);
        afterInsert(leaf->rightChild,lastIndex);
    }
}

void deleteRoot(node* leaf,int lastIndex)
{
    if(leaf!=NULL)
    {
        if(leaf->index==lastIndex)
        {
            node* temp= root;
            if(leaf->parent==NULL)
            {
                root=NULL;
                free(temp);
            }
            else
            {
                if(leaf->index==(leaf->parent->index*2))
                {
                    leaf->parent->leftChild=NULL;
                }
                else
                {
                    leaf->parent->rightChild=NULL;
                }
                leaf->index=root->index;
                leaf->leftChild=root->leftChild;
                if(leaf->leftChild!=NULL)
                    leaf->leftChild->parent=leaf;
                leaf->rightChild=root->rightChild;
                if(leaf->rightChild!=NULL)
                    leaf->rightChild->parent=NULL;
                leaf->parent=root->parent;
                root=leaf;
                free(temp);
            }
        }
        deleteRoot(leaf->leftChild,lastIndex);
        deleteRoot(leaf->rightChild,lastIndex);
    }
}

void afterDelete(node* leaf)
{
    if(leaf!=NULL)
    {
        while(1)
        {
            if(leaf->leftChild!=NULL && leaf->rightChild!=NULL)
            {
                if(leaf->data<leaf->leftChild->data||leaf->data<leaf->rightChild->data)
                {
                    if(leaf->leftChild->data>leaf->rightChild->data)
                    {
                        node* temp_parent= leaf->parent;
                        node* temp_leftChild=leaf->leftChild;
                        node* temp_leftChild_lc=temp_leftChild->leftChild;
                        node* temp_leftChild_rc=temp_leftChild->rightChild;
                        int temp_index=temp_leftChild->index;
                        temp_leftChild->index=leaf->index;
                        temp_leftChild->leftChild=leaf;
                        temp_leftChild->rightChild=leaf->rightChild;
                        if(temp_leftChild->rightChild!=NULL)
                            temp_leftChild->rightChild->parent=temp_leftChild;
                        temp_leftChild->parent=leaf->parent;
                        leaf->index=temp_index;
                        leaf->leftChild=temp_leftChild_lc;
                        if(leaf->leftChild!=NULL)
                            leaf->leftChild->parent=leaf;
                        leaf->rightChild=temp_leftChild_rc;
                        if(leaf->rightChild!=NULL)
                            leaf->rightChild->parent=leaf;
                        leaf->parent=temp_leftChild;
                        if(temp_leftChild->index==1)
                            root=temp_leftChild;


                        if(temp_parent!=NULL && temp_leftChild->index ==temp_parent->index*2)
                            temp_parent->leftChild=temp_leftChild;
                        else
                        {
                            if(temp_parent!=NULL)
                                temp_parent->rightChild=temp_leftChild;
                        }
                    }
                    else
                    {
                        node* temp_parent= leaf->parent;
                        node* temp_rightChild=leaf->rightChild;
                        node* temp_rightChild_lc=temp_rightChild->leftChild;
                        node* temp_rightChild_rc=temp_rightChild->rightChild;
                        int temp_index=temp_rightChild->index;
                        temp_rightChild->index=leaf->index;
                        temp_rightChild->rightChild=leaf;
                        temp_rightChild->leftChild=leaf->leftChild;
                        if(temp_rightChild->leftChild!=NULL)
                            temp_rightChild->leftChild->parent=temp_rightChild;
                        temp_rightChild->parent=leaf->parent;
                        leaf->index=temp_index;
                        leaf->leftChild=temp_rightChild_lc;
                        if(leaf->leftChild!=NULL)
                            leaf->leftChild->parent=leaf;
                        leaf->rightChild=temp_rightChild_rc;
                        if(leaf->rightChild!=NULL)
                            leaf->rightChild->parent=leaf;
                        leaf->parent=temp_rightChild;
                        if(temp_rightChild->index==1)
                            root=temp_rightChild;

                        if(temp_parent!=NULL && temp_rightChild->index ==temp_parent->index*2)
                            temp_parent->leftChild=temp_rightChild;
                        else
                        {
                            if(temp_parent!=NULL)
                                temp_parent->rightChild=temp_rightChild;
                        }
                    }
                }
                else
                    break;
            }
            else
            {
                if(leaf->leftChild==NULL)
                    break;
                else
                {
                    if(leaf->data<leaf->leftChild->data)
                    {
                        node* temp_parent= leaf->parent;
                        node* temp_leftChild=leaf->leftChild;
                        node* temp_leftChild_lc=temp_leftChild->leftChild;
                        node* temp_leftChild_rc=temp_leftChild->rightChild;
                        int temp_index=temp_leftChild->index;
                        temp_leftChild->index=leaf->index;
                        temp_leftChild->leftChild=leaf;
                        temp_leftChild->rightChild=leaf->rightChild;
                        if(temp_leftChild->rightChild!=NULL)
                            temp_leftChild->rightChild->parent=temp_leftChild;
                        temp_leftChild->parent=leaf->parent;
                        leaf->index=temp_index;
                        leaf->leftChild=temp_leftChild_lc;
                        if(leaf->leftChild!=NULL)
                            leaf->leftChild->parent=leaf;
                        leaf->rightChild=temp_leftChild_rc;
                        if(leaf->rightChild!=NULL)
                            leaf->rightChild->parent=leaf;
                        leaf->parent=temp_leftChild;
                        if(temp_leftChild->index==1)
                            root=temp_leftChild;

                        if(temp_parent!=NULL && temp_leftChild->index ==temp_parent->index*2)
                            temp_parent->leftChild=temp_leftChild;
                        else
                        {
                            if(temp_parent!=NULL)
                                temp_parent->rightChild=temp_leftChild;
                        }
                    }
                    else
                        break;
                }
            }
        }
    }
}

void list(node* leaf)
{
    if(root==NULL)
    {
        printf("%d->",leaf->data);
    }
    else
    {
        if(leaf!=NULL)
        {
            if(leaf->index==i)
            {
                printf("%d->",leaf->data);
                i++;
            }
            else
            {
                list(leaf->leftChild);
                list(leaf->rightChild);
            }
        }
        else
            list(root);
    }
}

void add(int pData)
{
    insertLeaf(root,createLeaf(pData));
    afterInsert(root,nodeCounter(root));
    isItEnd=0;
    list(root);
    printf("\n");
}

void del()
{
    if(root!=NULL)
    {
        deleteRoot(root,nodeCounter(root));
        afterDelete(root);
        list(root);
    }
    else
        printf("Node Yok!");
    printf("\n");
}

int main()
{
    add(5);
    add(6);
    add(25);
    add(35);
    add(45);
    add(7);
    add(10);
    add(40);
    add(40);
    add(-1);
    printf("\n");
    del();
    del();
    del();
    del();
    del();
    del();
    del();
    del();
    del();
}
