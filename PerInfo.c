#include <stdio.h>
typedef struct PerInfo{
    char name[10];
    char sex;
    int age;
    double height;



}PI;
int main(void){
    PI a1= {"otto", 'M', 26, 180.0 };
    PI *p=&a1;
    printf("%s,%c,%d,%.1f", p->name, a1.sex, a1.age, a1.height);







    return 0;
}
