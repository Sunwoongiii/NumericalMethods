#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float eval_f(float x);

int main(){
  float xl, xm, xh, e, delta;
  int i = 0;
  printf("\nType left bound of the interval: ");
  scanf("%f", &xl);

  printf("\nType right bound of the interval: ");
  scanf("%f", &xh);

  printf("\nType acceptable error interval: ");
  scanf("%f", &e);
  printf("\n");

  do{
    xm = (xl + xh) / 2.0;

    printf("%3dth Iteration Root: %f < with error %f >\n", ++i, (xl + xh)/2.0, (xl - xh) / 2.0);
    if(eval_f(xl) * eval_f(xm) == 0.0) break;
    else if(eval_f(xl) * eval_f(xm) < 0.0) xh = xm;
    else if(eval_f(xm) * eval_f(xh) < 0.0) xl = xm;
    else{
      printf("\nSomething Wrong!\n");
      break;
    }
  }while(xh - xl > e);
}

float eval_f(float x){
  float y;
  y = log(x + 5.0) + x;
  return y;
}