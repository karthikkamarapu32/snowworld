#include<stdio.h>
#include<stdlib.h>
#include "solve.h" 
int count(pathlist *head);

void append(int num,pathlist *head)
{
    pathlist *temp,*right;
    temp= (pathlist *)malloc(sizeof(pathlist));
    temp->data=num;
    right=(pathlist *)head;
    while(right->next != NULL)
    right=right->next;
    right->next =temp;
    right=temp;
    right->next=NULL;
}
 
 
 
void add( int num,pathlist *head)
{
    pathlist *temp;
    temp=(pathlist *)malloc(sizeof(pathlist));
    temp->data=num;
    if (head== NULL)
    {
    head=temp;
    head->next=NULL;
    }
    else
    {
    temp->next=head;
    head=temp;
    }
}
void addafter(int num, int loc,pathlist *head)
{
    int i;
    pathlist *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(pathlist *)malloc(sizeof(pathlist));
    temp->data=num;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}
 
 
 
void insert(int num,pathlist *head)
{
    int c=0;
    pathlist *temp;
    temp=head;
    if(temp==NULL)
    {
    add(num, head);
    }
    else
    {
    while(temp!=NULL)
    {
        if(temp->data<num)
        c++;
        temp=temp->next;
    }
    if(c==0)
        add(num, head);
    else if(c<count(head))
        addafter(num,++c, head);
    else
        append(num, head);
    }
}
 
 
 
int delete(int num,pathlist *head)
{
    pathlist *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
    if(temp->data==num)
    {
        if(temp==head)
        {
        head=temp->next;
        free(temp);
        return 1;
        }
        else
        {
        prev->next=temp->next;
        free(temp);
        return 1;
        }
    }
    else
    {
        prev=temp;
        temp= temp->next;
    }
    }
    return 0;
}
 
 
void  display(pathlist *r)
{
    r;//=head;
    if(r==NULL)
    {
    return;
    }
    while(r!=NULL)
    {
    printf("%d ",r->data);
    r=r->next;
    }
    printf("\n");
}
 
 
int count(pathlist *head)
{
    pathlist *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
    n=n->next;
    c++;
    }
    return c;
}
 
