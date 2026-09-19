#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}node;
node *addnode(int number){
    node *head=(node *)malloc(sizeof(node));
    head->data= number;
    head->next=NULL;
    return head;
}
node *headinsertnode(int number, node *head){
    node *newnode=(node *)malloc(sizeof(node));
    newnode->data=number;
    newnode->next=head;
    return newnode;
}
node *tailinsertnode(int number, node *head){
    node *tail=(node *)malloc(sizeof(node));
    node *anotherhead=head;
    tail->data=number;
    tail->next=NULL;
    while(anotherhead->next!=NULL){
        anotherhead=anotherhead->next;
    }
    anotherhead->next=tail;
    return head;
}
int main(void){
node *head=addnode(0);
node *A=headinsertnode(2, head);
node *B=tailinsertnode(1,A);
printf("data=");
while(B!=NULL){
printf("%d,", B->data);
node *temp=B;
B=B->next;
free(temp);
}

printf("NULL\n");
    return 0;
}