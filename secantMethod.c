#include <stdio.h>
#include <math.h>
#include <conio.h>

float eval_f(float x);
float fprime(float x1, float x2);

int main(){
  float x1, x2, xn, e;
  int i = 0;

  printf("\nType initial point : ");
  scanf("%f", &x1);
  printf("\nType second point : ");
  scanf("%f", &x2);
  printf("\nType acceptable error interval in y : ");
  scanf("%f", &e);

  do{
    xn = x1 - eval_f(x1) / fprime(x1,x2);
    x1 = x2;
    x2 = xn;
    printf("\n%3dth Iteration Root : %f < with error %f >\n", ++i, xn, fabs(eval_f(xn)));
    getch();
  }while(fabs(eval_f(xn)) > e);
}

float eval_f(float x){
  float b;
  b = log(x + 5.0) + x;
  return b;
}

float fprime(float x1, float x2){
  float b;
  b = (eval_f(x2) - eval_f(x1)) / (x2-x1);
  return b;
}