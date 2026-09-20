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
void printallnode(node *p){
    while(p!=NULL){
        printf("%d,", p->data);
        p=p->next;
    }
    printf("NULL\n");

}
void checklocation(int number, node *p){
    int i=0;
    while(p !=NULL && p->data!=number){
        i++;
        p=p->next; 
    }
    if(p==NULL){
        printf("false\n");
        i=114514;
    }
    printf("与%d距离%d步\n", number, i);
}
node *deletenote(int number, node *p){
    if(p==NULL){
        printf("false\n");
        return NULL;
    }
    if(number==1){
        node *o=p->next;
        free(p);
        printf("true\n");
        return o;
    }
    node *u=p;
    node *o=p->next;
    int i=1;
    while(p!=NULL){
        i++;
        if(i==number){
            u->next=o->next;
            printf("true\n");
            free(o);
            return p;
            break;
        }
        u=u->next;
        o=o->next;
        
    }
    return p;

}
node *verse(node *p){
    int i=0;
    node *p2=p;
    while(p!=NULL){
        i++;
        p=p->next;
    }
    int arr[i];
    int a;
    int b=0;
    int c=0;
    while(p2!=NULL){
        a=p2->data;
        arr[b]=a;
        b++;
        p2=p2->next;
    }
    node *p3=NULL;
    while(c<=i-1){
        p3=headinsertnode(arr[c], p3);
        c++;
    }
    return p3;
}
int main(void){
node *head=addnode(0);
node *A=headinsertnode(5, head);
node *C=headinsertnode(6, A);
node *D=headinsertnode(7, C);
node *E=headinsertnode(9, D);
node *F=headinsertnode(2, E);
node *B=tailinsertnode(1,F);
printf("data=");
printallnode(B);
checklocation(5, B);
node *G=verse(B);
printallnode(G);
}