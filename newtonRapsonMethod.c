#include <stdio.h>
#include <math.h>
#include <conio.h>

float eval_f(float x);
float diff_f(float x);

int main(){
  float xl, xm, e;
  int i;
  
  printf("\nType initial point: ");
  scanf("%f", &xl);

  printf("\nType acceptable error interval in y: ");
  scanf("%f", &e);

  i = 0;
  do{
    xm = xl - eval_f(xl) / diff_f(xl);
    xl = xm;
    printf("\n%3dth Iteration Root: %f < with error %f >\n", ++i, xm, fabs(eval_f(xm)));
    getch();
  }while(fabs(eval_f(xm)) > e);
}

float eval_f(float x){
  float b;
  b = log(x + 5.0) + x;
  return (b);
}

float diff_f(float x){
  float b;
  b = 1.0 / (x + 5.0) + 1.0;
  return (b);
}