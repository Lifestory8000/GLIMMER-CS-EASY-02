# Step 1. 指针与结构体
## 什么是指针？
### 如何在C语言中定义指针变量？指针变量的大小是固定的吗？其大小与什么有关？
- 用\*跟随p，得到指针变量\*p，可以有多种类型的指针变量比如int，char，double等；通过学习得知，指针变量的大小与指向的类型无关，而与编译平台有关。
### 写出以下代码的输出结果，并解释原因。、
- ``20，10``
- 第一个``int x = 10;int\* p = &x;\*p = 20;``通过第三步，更改了地址对应的值的大小，从而改变了地址指向变量的x的大小；
- 第二个``int arr[3] = {3, 6, 9};int *q = arr;int y = ++*arr  +  *++q;``先是让q指数表的地址，\*q指向arr[0]，第三步++是自增的意思，意思是arr[0]还要再加一得到4；++q是把数表从[0]挪到[1]，现在\*++q指的是arr[1]=6，最后4+6=10
### 什么是野指针？简述其危害。如何避免产生野指针？
- 野指针就是指针指向不确定（随机访问，电脑核心数据地址），或者说地址已经没了，或内存已经被释放（这个不是很懂）的指针；野指针可能会导致C程序在运行的时候崩溃，或者是篡改电脑内的关键数据引发危险；使用指针是要初始化，不要使用未初始化的指针，如果不确定则让它先指向NULL，使用前记得检查指向的地址，不要让其指向危险地址，释放其内存后要指向NULL，不要继续使用。

### 尝试设计一个真正有效的swap()函数
````
#include <stdio.h>
void swap(int *a, int  *b){
  int temp = *a;
  *a = *b;
  *b = temp;
  printf("%d, %d\n", *a, *b);
}

int main(){
  int a = 10;
  int b = 20;
  swap(&a, &b);//交换地址
  int temp=0;
  printf("%d, %d\n", a, b);
  return 0;
}
````
## 什么是结构体？
### 请你完成一个PerInfo结构体的定义，成员组成如下。了解一下typedef关键字与结构体的一般用法，利用typedef为你刚刚定义的结构体取一个别名。提交最终的结构体定义。
````
1. 个人姓名（字符型数组，长度为10个字节）
2. 性别（字符型）
3. 年龄（整型）
4. 身高（双精度浮点型）
````
````
#include <stdio.h>
typedef struct PerInfo{
    char name[10];\\10字节（对齐数1）
    char sex;\\1
    int age;\\4
    double height;\\8
}PI;
int main(void){
    PI a1= {"otto", 'M', 26, 180.0 };
    PI *p=&a1;
    printf("%s,%c,%d,%.1f", p->name, a1.sex, a1.age, a1.height);
    return 0;
}

````
### 了解并说明结构体指针的含义。
- 结构体指针是指向结构体变量的指针变量，通过把结构体变量的地址交给结构体指针，使得这个指针可以访问结构体变量中的各个变量（成员）。可以便携地修改结构体的成员的具体值。举个例子
````
PI *p=&a1;\\这里把结构体a1的地址发给p
 p->name="jakc"//更改name
 (*p).sex='F'\\另外一种更改方式，p相当于&a1，*p相当于a1本身
 a1.age=99\\直接改也行
````
### 了解一下结构体的内存对齐规则，据此计算一下你刚刚定义的结构体占用字节的大小（可用sizeof运算符验证计算结果）。提交计算过程。(此外，你还可以尝试更改一下结构体中成员的定义顺序，看看对结构体占用字节数的影响)
- 我预计是30字节
- 然而事实上是24   ``每个成员的起始地址，必须是它自身对齐数的整数倍。``
- name字节10，对齐数是1，已经满足（不必是4的倍数），不用再补2；sex对齐数是1,10是1的倍数，不用补；现在字节11，需要补到12，满足是4的倍数。现在字节数16，满足是八的倍数，总字节数16。而``结构体总大小，必须是结构体中最大对齐数的整数倍。``结构体最大对齐数为8，24是八的倍数，不用调整（我一开始以为是最大字节数的倍数，事实上，**字节数并不影响类型的对齐数**）
- 调整后的程序附下
````
#include <stdio.h>
typedef struct PerInfo{
    double height;
    int age;
    char name[10];
    char sex;

}PI;
int main(void){
    PI a1= {180.0, 23, "oto", 'M'};
    PI *p=&a1;
    printf("%s,%c,%d,%.1f\n", p->name, a1.sex, a1.age, a1.height);
    printf("sizeof(a1)=%8zu\n", sizeof(struct PerInfo));
    return 0;//调了之后好像还是24
}

````
# Step2. 链操作
## 什么是链表？
### 请对比链表和数组的存储，讲讲链表和数组的区别
- 数组是连续储存，每个元素占据的内存固定，整体来说占据空间更小（？）但是占据空间固定，空间利用率更小，而且数组在初始化后趋于固定，增删数据非常麻烦。
- 链表相比数组储存更为分散化，不连续，每个节点申请一个指针，且储存位置不可随意查找，相对而言空间利用率更高，增删数据非常方便，可供后续调整，问题是增删数据需要从``head``开始一个个读取，稍微不是那么快。但是它也存在野指针的危险。
### 简述单向链表节点的结构特点。定义一个只存储一个整数的单向链表节点。
- 单向链表节点由存放数据的区域和存放下一个节点地址的区域（或者叫指针）组成，每一个节点都是这样，最后一个节点存放的下一个地址是NULL。它只能从头节点走向NULL，不可来回走。
~~其实下面这段代码我基本上没搞懂，我相当于是边报错边改来的~~
````
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}node;
int main(void){
node *n1 = (node *)malloc(sizeof(node));
node *p=n1;
p->data=2;
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
````
## 添加元素：
````
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
````
## 查找元素
- 全部输出：
````
void printallnode(node *p){
    while(p!=NULL){
        printf("%d,", p->data);
        p=p->next;
    }
````
- 实测``printallnode(B);``后没有改变B的指向
- 查找元素
````
void checklocation(int number, node *p){
    int i=0;
    while(p !=NULL && p->data!=number){\\不能让p=NULL，否则野指针（这个试验过）
        i++;
        p=p->next; 
    }
    if(p==NULL){
        printf("false\n");
        i=114514;\\如果出现114514步，则说明没有找到
    }
    printf("与%d距离%d步\n", number, i);
}

````
## 删除和更改
~~这个代码我改了一下午，依旧报错，这里展示错误代码~~
````
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
node *deletenote(int number, node *p){\\就是这里开始，好诡异啊
    node *o=p;
    node *u=p;
    if(p==NULL){
        printf("false\n");
        return NULL;
    }
    if(p!=NULL && p->next==NULL && number==1){
        o=p->next;
        printf("true\n");
        return o;
    }
    o=p->next;
    int i=1;
    while(p!=NULL){
        i++;
        if(i==number){
            u->next=o->next;
            printf("true\n");
            return u;
            break;
        }
        o=o->next;
        u=u->next;
    }

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
node *G=deletenote(1, B);
printallnode(G);
}
````
### 花费了一个下午加晚上一直没研究出来，最终求助deepseek（但是我还是完全搞不懂，稍微标注一些我能看懂的）
````
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
    if(p==NULL){    \\如果p是NULL，直接输出false
        printf("false\n");
        return NULL;\\返回一个NULL，虽然p本身就是NULL，相当于什么也不改变
    }
    if(number==1){\\如果要删除第一个节点，且p不是NULL
        node *o=p->next;\\从p的next作为第一个节点地址，返回一个新的节点p    
        free(p);
        printf("true\n");
        return o;
    }
    node *u=p;
    node *o=p->next;\\先移动一位，因为i是从1开始的（o相当于是从p的第二节点作为第一个节点的）
    int i=1;
    while(p!=NULL){
        i++;
        if(i==number){
            u->next=o->next;\\（把u的next推到o的next，但是**u本身的data是不变的**，意思就是把原本的p的这个位置的节点给删除了（凭空跳过了一个data）（u是一个node类型的指针，指向的就是p，修改u也会修改原有的p））
            printf("true\n");
            free(o);\\没搞懂为啥要释放内存
            return p;
            break;
        }
        u=u->next;\\（把o和u向后推一个节点）
        o=o->next;
        
    }
    return p;

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
node *G=deletenote(4, B);
printallnode(G);
}
````
## 反转函数：
### 请根据上面双指针的思想，设计一个函数，传入头指针，然后将链表倒置，头指针指向新链表的第一个节点。
- 这里第一时间想到的是建立一个数表，然后倒序输入。
````
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
````



























