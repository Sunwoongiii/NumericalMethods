#include <stdio.h>
#include <math.h>

float eval_f(float a);
float find_xm(float xl, float xh);

int main(){
  float xl, xm, xh, e;
  int i = 0;

  printf("\nType left bound of the interval: ");
  scanf("%f", &xl);

  printf("\nType right bound of the interval: ");
  scanf("%f", &xh);

  printf("\nType acceptable error interval: ");
  scanf("%f", &e);

  do{
    xm = find_xm(xl, xh);
    if(eval_f(xl) * eval_f(xm) == 0.0)break;
    else if(eval_f(xl) * eval_f(xm) < 0.0) xh = xm;
    else if(eval_f(xm) * eval_f(xh) < 0.0) xl = xm;
    else {
      printf("\nSomething Wrong!\n");
      break;
    }
    printf("\n%3dth Iteration Root : %f < with error %f >\n", ++i, xm, eval_f(xm));
  }while(fabs(eval_f(xm)) > e);
}

float eval_f(float a){
  float b = log(a+5.0) + a;
  return b;
}

float find_xm(float xl, float xh){
  float b;
  b = (eval_f(xh) * xl - eval_f(xl) * xh ) / (eval_f(xh) - eval_f(xl));
  return b;
}