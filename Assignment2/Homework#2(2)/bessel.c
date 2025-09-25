#include <math.h>
#include "bessel.h"

// 베셀 함수 J0(x)의 정확한 구현
double bessel_j0(double x) {
    if (fabs(x) < 8.0) {
        // 작은 x에 대한 급수 전개
        double y = x * x;
        return (1.0 - y/4.0 + y*y/64.0 - y*y*y/2304.0 + 
                y*y*y*y/147456.0 - y*y*y*y*y/14745600.0);
    } else {
        // 큰 x에 대한 점근 공식
        double z = 8.0 / x;
        double y = z * z;
        double xx = x - 0.785398164;
        double p0 = 1.0;
        double p1 = -0.1098628627e-2;
        double p2 = 0.2734510407e-4;
        double p3 = -0.2073370639e-5;
        double p4 = 0.2093887211e-6;
        double q0 = -0.1562499995e-1;
        double q1 = 0.1430488765e-3;
        double q2 = -0.6911147651e-5;
        double q3 = 0.7621095161e-6;
        double q4 = -0.934945152e-7;
        double p = p0 + y*(p1 + y*(p2 + y*(p3 + y*p4)));
        double q = z*(q0 + y*(q1 + y*(q2 + y*(q3 + y*q4))));
        return sqrt(0.636619772/x) * (p*cos(xx) - q*sin(xx));
    }
}

// 베셀 함수 J1(x)의 정확한 구현
double bessel_j1(double x) {
    if (fabs(x) < 8.0) {
        double y = x * x;
        return x * (0.5 - y/16.0 + y*y/384.0 - y*y*y/18432.0 + 
                   y*y*y*y/1474560.0 - y*y*y*y*y/176947200.0);
    } else {
        double z = 8.0 / x;
        double y = z * z;
        double xx = x - 2.356194491;
        double p0 = 1.0;
        double p1 = 0.183105e-2;
        double p2 = -0.3516396496e-4;
        double p3 = 0.2457520174e-5;
        double p4 = -0.240337019e-6;
        double q0 = 0.04687499995;
        double q1 = -0.2002690873e-3;
        double q2 = 0.8449199096e-5;
        double q3 = -0.88228987e-6;
        double q4 = 0.105787412e-6;
        double p = p0 + y*(p1 + y*(p2 + y*(p3 + y*p4)));
        double q = z*(q0 + y*(q1 + y*(q2 + y*(q3 + y*q4))));
        return sqrt(0.636619772/x) * (p*cos(xx) - q*sin(xx));
    }
}

// 베셀 함수 J0의 도함수 = -J1(x)
double bessel_j0_derivative(double x) {
    return -bessel_j1(x);
}