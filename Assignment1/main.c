#include <stdio.h>
#include "nr.h"

void get_epsf(float* eps){
    *eps = 1.0f;
    while(1.0f + *eps != 1.0f){
        *eps /= 2;
    }
   *eps *= 2;
}

void get_epsd(double* eps){
    *eps = 1.0;
    while(1.0 + *eps != 1.0){
        *eps /= 2;
    }
   *eps *= 2;
}

int main(){
    int ibeta, it, irnd, ngrd, machep, negep, iexp, minexp, maxexp;
    float eps, epsneg, xmin, xmax;
    double epsd, epsnegd, xmind, xmaxd;

    machar(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, 
        &minexp, &maxexp, &eps, &epsneg, &xmin, &xmax);
    printf("Float Machine Accuracy(machar): \t%0.20f\n", eps);
    
    get_epsf(&eps);
    printf("Float Machine Accuracy(get_eps): \t%0.20f\n", eps);

    machar2(&ibeta, &it, &irnd, &ngrd, &machep, &negep, &iexp, 
        &minexp, &maxexp, &epsd, &epsnegd, &xmind, &xmaxd);

    printf("Double Machine Accuracy(machar): \t%0.20f\n", epsd);
    
    get_epsd(&epsd);
    printf("Double Machine Accuracy(get_eps): \t%0.20f\n", epsd);

    return 0;
}