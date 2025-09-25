#include <stdio.h>
#include <math.h>
#include "nr_wrap.h"
static long iterations;

float muller(float (*func)(float), float x1, float x2, float xacc)
{
  const int MAXIT = 30;
  float x3, h1, h2, f1, f2, f3, d1, d2, a0, a1, a2, disc, den1, den2, dx;

  iterations = 0;
  x3 = 0.5f * (x1 + x2);

  for (int j = 1; j <= MAXIT; j++) {
    iterations++;
    f1 = (*func)(x1);
    f2 = (*func)(x2);
    f3 = (*func)(x3);

    h1 = x1 - x3;
    h2 = x2 - x3;
    d1 = f1 - f3;
    d2 = f2 - f3;

    if (fabsf(h1 * h2) < 1.0e-14f) break;

    a0 = f3;
    a1 = (d2 * h1 * h1 - d1 * h2 * h2) / (h1 * h2 * (h1 - h2));
    a2 = (d1 * h2 - d2 * h1) / (h1 * h2 * (h1 - h2));

    disc = a1 * a1 - 4.0f * a0 * a2;
    if (disc < 0.0f) disc = 0.0f;

    den1 = a1 + sqrtf(disc);
    den2 = a1 - sqrtf(disc);

    if (fabsf(den1) > fabsf(den2))
      dx = -2.0f * a0 / den1;
    else
      dx = -2.0f * a0 / den2;

    x1 = x2;
    x2 = x3;
    x3 += dx;

    if (fabsf(dx) < xacc) return x3;
  }

  nrerror("Too many iterations in muller");
  return 0.0f;
}

long get_muller_iterations(void)
{
  return iterations;
}
