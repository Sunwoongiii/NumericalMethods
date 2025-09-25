#ifndef BESSEL_H
#define BESSEL_H

// 베셀 함수 J0(x) 계산
double bessel_j0(double x);

// 베셀 함수 J1(x) 계산  
double bessel_j1(double x);

// 베셀 함수 J0의 도함수 (-J1)
double bessel_j0_derivative(double x);

#endif