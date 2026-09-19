#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}node;
int main(void){
node *n1 = (node *)malloc(sizeof(node));
node *p=n1;
p->data=0;
p->next=NULL;
node *head=n1;
printf("data=\n");
while(head!=NULL){
printf("%d", head->data);
node *temp=head;
head=head->next;
free(temp);
}


    return 0;
}