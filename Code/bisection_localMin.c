#include <stdio.h>
#include <conio.h>
#include <math.h>

float eval_f(float x);

int main(){
  float xl, xm, xr, e, s, fxl, fxm, fxr;
  int i = 0;

  printf("\nType initial point Xl : ");
  scanf("%f", &xl);
  printf("\nType initial step S : ");
  scanf("%f", &s);
  printf("\nType acceptable error interval E : ");
  scanf("%f", &e);

  while(s > e){
    xm = xl + s;
    xr = xm + s;
    i++;

    fxl = eval_f(xl);
    fxm = eval_f(xm);
    fxr = eval_f(xr);

    if(fxm < fxl && fxm < fxr){
      s = s/2.0;
      continue;
    }
    printf("%3dth iteration : x = %8.5f f(x) = %8.5f\n", i, xm, fxm);
    xl = xm;
  }
  printf("\nf(x) has local minimum at %8.5f with error %8.5f\n", xm, e);
  printf("f(x) = %g \n", fxm);
}

float eval_f(float x){
  float a;
  a = 2.5*x*x - 7.0*x + 2.5;
  return(a);
}