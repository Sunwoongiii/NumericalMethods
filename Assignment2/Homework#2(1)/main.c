#include <stdio.h>
#include <math.h>

float bessj0(float x);
float bessj1(float x);
float rtbis(float (*func)(float), float x1, float x2, float xacc);
float rtflsp(float (*func)(float), float x1, float x2, float xacc);
float rtnewt(void (*funcd)(float, float *, float *), float x1, float x2, float xacc);
float rtsafe(void (*funcd)(float, float *, float *), float x1, float x2, float xacc);
float rtsec(float (*func)(float), float x1, float x2, float xacc);
void zbrak(float (*fx)(float), float x1, float x2, int n, float xb1[], float xb2[], int *nb);

void bessj0_and_derivative(float x, float *f, float *df){
  *f = bessj0(x);
  *df = -bessj1(x);
}

int main(){
  float xb1[20], xb2[20];
  int nb, i;
  float xacc = 1.0e-6;

  printf("Finding roots of J0(x) int [1.0, 10.0]\n\n");
  zbrak(bessj0, 1.0, 10.0, 100, xb1, xb2, &nb);

  printf("Found %d bracketing intervals: \n", nb);
  for(i = 1; i <= nb; i++){
    printf("Interval %d: [%.6f, %.6f]\n",i, xb1[i], xb2[i]);

    printf("  Bisection: %.8f\n", rtbis(bessj0, xb1[i], xb2[i], xacc));
    printf("  False Position: %.8f\n", rtflsp(bessj0, xb1[i], xb2[i], xacc));
    printf("  Secant: %.8f\n", rtsec(bessj0, xb1[i], xb2[i], xacc));
    printf("  Newton-Raphson: %.8f\n", rtnewt(bessj0_and_derivative, xb1[i], xb2[i], xacc));
    printf("  Newton with bracketing: %.8f\n", rtsafe(bessj0_and_derivative, xb1[i], xb2[i], xacc));
    printf("\n");
  }
  return 0;
}