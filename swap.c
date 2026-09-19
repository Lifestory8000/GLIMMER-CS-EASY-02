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
  swap(&a, &b);
  int temp=0;
  printf("%d, %d\n", a, b);
  return 0;
}