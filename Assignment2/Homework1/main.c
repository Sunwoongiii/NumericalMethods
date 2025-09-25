#include <stdio.h>
#include <math.h>
#include <windows.h>

#include "nr_wrap.h"
#include "muller.h"

static long func_calls, df_calls;
static long total_iters[6], total_fcalls[6], total_dfcalls[6];
static double total_time[6];
static const char *names[6] = {
  "Bisection", "LinearInterp", "Secant",
  "Newton", "NewtonSafe", "Muller"
};

float f_wrapper(float x) {
  func_calls++;
  return bessj0(x);
}
void fdf_wrapper(float x, float *f, float *df) {
  func_calls++;
  df_calls++;
  *f = bessj0(x);
  *df = -bessj1(x);
}

enum { I_BISEC=0, I_FLSP, I_SEC, I_NEW, I_SAFE, I_MULL };

static LARGE_INTEGER qpc_freq;

void timer_init(void) {
  QueryPerformanceFrequency(&qpc_freq);
}

double timer_ms(void) {
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (double)now.QuadPart * 1000.0 / (double)qpc_freq.QuadPart;
}

int main(void) {
  timer_init();

  const int NX = 1000;
  const float x1 = 1.0f, x2 = 10.0f, tol = 1e-6f;
  float xb1[NX], xb2[NX];
  int nb = 0;

  zbrak(f_wrapper, x1, x2, NX, xb1, xb2, &nb);
  printf("Found %d roots in [%.1f, %.1f]\n\n", nb, x1, x2);

  for (int i = 0; i < 6; i++) {
    total_iters[i] = total_fcalls[i] = total_dfcalls[i] = 0;
    total_time[i] = 0.0;
  }

  for (int k = 1; k <= nb; k++) {
    float a = xb1[k], b = xb2[k];
    printf("Root %d: bracket [%.6f, %.6f]\n", k, a, b);

    for (int m = 0; m < 6; m++) {
      double t0 = timer_ms();
      long before_f = func_calls, before_df = df_calls;
      float root;
      long iters = 0;

      switch (m) {
        case I_BISEC:
          root = rtbis(f_wrapper, a, b, tol);
          break;
        case I_FLSP:
          root = rtflsp(f_wrapper, a, b, tol);
          break;
        case I_SEC:
          root = rtsec(f_wrapper, a, b, tol);
          break;
        case I_NEW:
          root = rtnewt(fdf_wrapper, a, b, tol);
          break;
        case I_SAFE:
          root = rtsafe(fdf_wrapper, a, b, tol);
          break;
        case I_MULL:
          root = muller(f_wrapper, a, b, tol);
          iters = get_muller_iterations();
          break;
      }

      double t1 = timer_ms();
      long fc = func_calls - before_f;
      long dfc = df_calls - before_df;
      double tms = t1 - t0;

      if (m != I_MULL) iters = fc;

      total_iters[m]   += iters;
      total_fcalls[m]  += fc;
      total_dfcalls[m] += dfc;
      total_time[m]    += tms;

      printf("  %-12s root=%.8f iters=%4ld f-calls=%4ld df-calls=%4ld time=%.3fms\n",
             names[m], root, iters, fc, dfc, tms);
    }
    printf("\n");
  }

  printf("Summary (averaged over %d roots)\n", nb);
  printf("Method         AvgIters  AvgFcalls  AvgDf  AvgTime(ms)\n");
  printf("------         --------  ---------  -----  ----------\n");
  for (int m = 0; m < 6; m++) {
    printf("%-14s %8.1f %9.1f %6.1f %12.3f\n",
           names[m],
           (double)total_iters[m]   / nb,
           (double)total_fcalls[m]  / nb,
           (double)total_dfcalls[m] / nb,
           total_time[m]            / nb
    );
  }

  return 0;
}
