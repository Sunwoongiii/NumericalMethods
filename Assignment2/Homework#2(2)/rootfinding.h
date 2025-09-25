#ifndef ROOTFINDING_H
#define ROOTFINDING_H

// 이분법 (rtbis)
double rtbis(double (*func)(double), double x1, double x2, double xacc, 
             int *iterations, int *func_calls);

// 선형 보간법 / False Position (rtflsp)
double rtflsp(double (*func)(double), double x1, double x2, double xacc,
              int *iterations, int *func_calls);

// 할선법 (rtsec)  
double rtsec(double (*func)(double), double x1, double x2, double xacc,
             int *iterations, int *func_calls);

// 뉴턴-랩슨법 (rtnewt)
double rtnewt(double (*func)(double), double (*dfunc)(double), double x1, 
              double xacc, int *iterations, int *func_calls);

// 브래키팅을 결합한 안전한 뉴턴법 (rtsafe)
double rtsafe(double (*func)(double), double (*dfunc)(double), 
              double x1, double x2, double xacc, int *iterations, int *func_calls);

// 뮬러 방법 (muller)
double muller(double (*func)(double), double x0, double x1, double x2, 
              double xacc, int *iterations, int *func_calls);

#endif