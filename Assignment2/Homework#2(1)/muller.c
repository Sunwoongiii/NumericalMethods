#include <stdio.h>
#include <math.h>
#include <complex.h>

#define MAX_ITER 1000
#define TOLERANCE 1e-6

double bessel_j0(double x) {
    if (fabs(x) < 8.0) {
        double y = x * x;
        return (1.0 - y/4.0 + y*y/64.0 - y*y*y/2304.0 + 
                y*y*y*y/147456.0 - y*y*y*y*y/14745600.0);
    } else {
        double z = 8.0 / x;
        double y = z * z;
        double xx = x - 0.785398164;
        double p = 1.0 - 0.1098628627e-2*y + 0.2734510407e-4*y*y;
        double q = z*(-0.1562499995e-1 + 0.1430488765e-3*y);
        return sqrt(0.636619772/x) * (p*cos(xx) - q*sin(xx));
    }
}

double muller_method(double (*func)(double), double x0, double x1, double x2) {
    int iter = 0;

    for (iter = 0; iter < MAX_ITER; iter++) {
        double f0 = func(x0);
        double f1 = func(x1);
        double f2 = func(x2);

        double h1 = x1 - x0;
        double h2 = x2 - x1;
        double d1 = (f1 - f0) / h1;
        double d2 = (f2 - f1) / h2;

        double a = (d2 - d1) / (h2 + h1);
        double b = a * h2 + d2;
        double c = f2;

        double discriminant = b*b - 4*a*c;
        double dx;

        if (discriminant >= 0) {
            double sqrt_disc = sqrt(discriminant);
            if (fabs(b + sqrt_disc) > fabs(b - sqrt_disc)) {
                dx = -2*c / (b + sqrt_disc);
            } else {
                dx = -2*c / (b - sqrt_disc);
            }
        } else {
            dx = -c / b;
        }

        double x3 = x2 + dx;

        if (fabs(dx) < TOLERANCE * fabs(x3)) {
            printf("Converged after %d iterations\n", iter + 1);
            return x3;
        }

        x0 = x1;
        x1 = x2;
        x2 = x3;
    }

    printf("Maximum iterations reached\n");
    return x2;
}

int main() {
    printf("Muller Method for finding roots of Bessel J0(x)\n");
    printf("===============================================\n");

    double roots[][3] = {
        {2.0, 2.2, 2.5},    
        {8.0, 8.5, 9.0}     
    };

    for (int i = 0; i < 2; i++) {
        printf("\nFinding root near %.1f:\n", roots[i][1]);
        double root = muller_method(bessel_j0, roots[i][0], roots[i][1], roots[i][2]);
        printf("Root found: %.8f\n", root);
        printf("J0(%.8f) = %.2e\n", root, bessel_j0(root));
    }
    return 0;
}