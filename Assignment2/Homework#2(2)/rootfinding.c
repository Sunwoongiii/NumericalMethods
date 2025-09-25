#include <math.h>
#include <stdio.h>
#include "rootfinding.h"

#define MAXIT 100

// 이분법 구현
double rtbis(double (*func)(double), double x1, double x2, double xacc, 
             int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    double f = func(x1);
    double fmid = func(x2);
    (*func_calls) += 2;

    if (f * fmid >= 0.0) {
        printf("Root must be bracketed for bisection\n");
        return NAN;
    }

    double dx;
    double rtb = f < 0.0 ? (dx = x2 - x1, x1) : (dx = x1 - x2, x2);

    for (int j = 0; j < MAXIT; j++) {
        dx *= 0.5;
        double xmid = rtb + dx;
        fmid = func(xmid);
        (*func_calls)++;
        (*iterations)++;

        if (fmid <= 0.0) rtb = xmid;
        if (fabs(dx) < xacc || fmid == 0.0) return rtb;
    }

    printf("Too many bisections\n");
    return rtb;
}

// 선형 보간법 (False Position) 구현
double rtflsp(double (*func)(double), double x1, double x2, double xacc,
              int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    double fl = func(x1);
    double fh = func(x2);
    (*func_calls) += 2;

    if (fl * fh >= 0.0) {
        printf("Root must be bracketed for false position\n");
        return NAN;
    }

    double xl = x1, xh = x2;
    if (fl < 0.0) {
        xl = x1; xh = x2;
    } else {
        xl = x2; xh = x1;
        double temp = fl; fl = fh; fh = temp;
    }

    double rtf = xl;
    double dx = xh - xl;

    for (int j = 0; j < MAXIT; j++) {
        rtf = xl + dx * fl / (fl - fh);
        double f = func(rtf);
        (*func_calls)++;
        (*iterations)++;

        if (f < 0.0) {
            double del = xl - rtf;
            xl = rtf;
            fl = f;
            if (fabs(del) < xacc || f == 0.0) return rtf;
        } else {
            double del = xh - rtf;
            xh = rtf;
            fh = f;
            if (fabs(del) < xacc || f == 0.0) return rtf;
        }
        dx = xh - xl;
    }

    printf("Maximum iterations exceeded in rtflsp\n");
    return rtf;
}

// 할선법 구현
double rtsec(double (*func)(double), double x1, double x2, double xacc,
             int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    double f1 = func(x1);
    double f2 = func(x2);
    (*func_calls) += 2;

    if (fabs(f1) > fabs(f2)) {
        double temp = x1; x1 = x2; x2 = temp;
        temp = f1; f1 = f2; f2 = temp;
    }

    for (int j = 0; j < MAXIT; j++) {
        if (fabs(f2 - f1) < 1e-15) break;

        double dx = (x2 - x1) * f2 / (f2 - f1);
        x1 = x2;
        f1 = f2;
        x2 += dx;
        f2 = func(x2);
        (*func_calls)++;
        (*iterations)++;

        if (fabs(dx) < xacc || f2 == 0.0) return x2;
    }

    printf("Maximum iterations exceeded in rtsec\n");
    return x2;
}

// 뉴턴-랩슨법 구현
double rtnewt(double (*func)(double), double (*dfunc)(double), double x1, 
              double xacc, int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    for (int j = 0; j < MAXIT; j++) {
        double f = func(x1);
        double df = dfunc(x1);
        (*func_calls) += 2;
        (*iterations)++;

        if (fabs(df) < 1e-15) {
            printf("Derivative too small in rtnewt\n");
            break;
        }

        double dx = f / df;
        x1 -= dx;

        if (fabs(dx) < xacc) return x1;
    }

    printf("Maximum iterations exceeded in rtnewt\n");
    return x1;
}

// 브래키팅을 결합한 안전한 뉴턴법
double rtsafe(double (*func)(double), double (*dfunc)(double), 
              double x1, double x2, double xacc, int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    double f1 = func(x1);
    double f2 = func(x2);
    (*func_calls) += 2;

    if (f1 * f2 >= 0.0) {
        printf("Root must be bracketed in rtsafe\n");
        return NAN;
    }

    double xl, xh;
    if (f1 < 0.0) {
        xl = x1; xh = x2;
    } else {
        xh = x1; xl = x2;
    }

    double rts = 0.5 * (x1 + x2);
    double dxold = fabs(x2 - x1);
    double dx = dxold;

    double f = func(rts);
    double df = dfunc(rts);
    (*func_calls) += 2;

    for (int j = 0; j < MAXIT; j++) {
        (*iterations)++;

        if ((((rts - xh) * df - f) * ((rts - xl) * df - f) > 0.0) ||
            (fabs(2.0 * f) > fabs(dxold * df))) {
            // 이분법 사용
            dxold = dx;
            dx = 0.5 * (xh - xl);
            rts = xl + dx;
            if (xl == rts) return rts;
        } else {
            // 뉴턴법 사용
            dxold = dx;
            dx = f / df;
            double temp = rts;
            rts -= dx;
            if (temp == rts) return rts;
        }

        if (fabs(dx) < xacc) return rts;

        f = func(rts);
        df = dfunc(rts);
        (*func_calls) += 2;

        if (f < 0.0) {
            xl = rts;
        } else {
            xh = rts;
        }
    }

    printf("Maximum iterations exceeded in rtsafe\n");
    return rts;
}

// 뮬러 방법 구현
double muller(double (*func)(double), double x0, double x1, double x2, 
              double xacc, int *iterations, int *func_calls) {
    *func_calls = 0;
    *iterations = 0;

    for (int j = 0; j < MAXIT; j++) {
        double f0 = func(x0);
        double f1 = func(x1);
        double f2 = func(x2);
        (*func_calls) += (j == 0) ? 3 : 1;
        (*iterations)++;

        double h1 = x1 - x0;
        double h2 = x2 - x1;
        double d1 = (f1 - f0) / h1;
        double d2 = (f2 - f1) / h2;

        double a = (d2 - d1) / (h2 + h1);
        double b = a * h2 + d2;
        double c = f2;

        double discriminant = b * b - 4.0 * a * c;
        double dx;

        if (discriminant >= 0.0) {
            double sqrt_disc = sqrt(discriminant);
            if (fabs(b + sqrt_disc) > fabs(b - sqrt_disc)) {
                dx = -2.0 * c / (b + sqrt_disc);
            } else {
                dx = -2.0 * c / (b - sqrt_disc);
            }
        } else {
            // 복소수 경우, 실부만 사용
            dx = -c / b;
        }

        double x3 = x2 + dx;

        if (fabs(dx) < xacc) return x3;

        x0 = x1;
        x1 = x2;
        x2 = x3;
    }

    printf("Maximum iterations exceeded in muller\n");
    return x2;
}