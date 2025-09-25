#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "bessel.h"
#include "rootfinding.h"

#define XACC 1e-6
#define NMAX 100

typedef struct {
    char method_name[30];
    double root;
    int iterations;
    int func_calls;
    double time_ms;
    double error;
} Result;

int zbrak(double (*func)(double), double x1, double x2, int n, double *xb1, double *xb2) {
    int nb = 0;
    double dx = (x2 - x1) / n;
    double x = x1;
    double fp = func(x);

    for (int i = 0; i < n; i++) {
        x += dx;
        double fc = func(x);
        if (fc * fp < 0.0) {
            xb1[nb] = x - dx;
            xb2[nb] = x;
            nb++;
        }
        fp = fc;
    }
    return nb;
}

double known_roots[] = {2.4048255577, 5.5200781103, 8.6537279129};

double find_nearest_known_root(double root) {
    double min_diff = fabs(root - known_roots[0]);
    double nearest = known_roots[0];

    for (int i = 1; i < 3; i++) {
        double diff = fabs(root - known_roots[i]);
        if (diff < min_diff && known_roots[i] <= 10.0) {
            min_diff = diff;
            nearest = known_roots[i];
        }
    }
    return nearest;
}

int main() {
    printf("베셀 함수 J0(x) 근 찾기 - 6가지 방법 비교\n");
    printf("=========================================\n\n");

    // 브래키팅으로 근이 있는 구간들 찾기
    double xb1[10], xb2[10];
    int nb = zbrak(bessel_j0, 1.0, 10.0, 50, xb1, xb2);

    printf("구간 [1.0, 10.0]에서 찾은 브래킷: %d개\n", nb);
    for (int i = 0; i < nb; i++) {
        printf("브래킷 %d: [%.3f, %.3f]\n", i+1, xb1[i], xb2[i]);
    }

    Result results[6 * 10];  
    int result_count = 0;

    char* method_names[] = {"Bisection", "Linear Interp", "Secant", 
                           "Newton-Raphson", "Newton w/Bracket", "Muller"};

    printf("\n%-20s %-12s %-8s %-10s %-10s %-10s\n", 
           "Method", "Root", "Iter", "FuncCalls", "Time(ms)", "Error");
    printf("--------------------------------------------------------------------\n");

    for (int method = 0; method < 6; method++) {
        for (int i = 0; i < nb; i++) {
            clock_t start = clock();
            double root;
            int iterations, func_calls;

            switch (method) {
                case 0: // Bisection
                    root = rtbis(bessel_j0, xb1[i], xb2[i], XACC, &iterations, &func_calls);
                    break;
                case 1: // Linear Interpolation (False Position)
                    root = rtflsp(bessel_j0, xb1[i], xb2[i], XACC, &iterations, &func_calls);
                    break;
                case 2: // Secant
                    root = rtsec(bessel_j0, xb1[i], xb1[i] + 0.01, XACC, &iterations, &func_calls);
                    break;
                case 3: // Newton-Raphson
                    root = rtnewt(bessel_j0, bessel_j0_derivative, (xb1[i] + xb2[i])/2, 
                                 XACC, &iterations, &func_calls);
                    break;
                case 4: // Newton with Bracketing
                    root = rtsafe(bessel_j0, bessel_j0_derivative, xb1[i], xb2[i], 
                                 XACC, &iterations, &func_calls);
                    break;
                case 5: // Muller
                    root = muller(bessel_j0, xb1[i], (xb1[i] + xb2[i])/2, xb2[i], 
                                 XACC, &iterations, &func_calls);
                    break;
            }

            clock_t end = clock();
            double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

            if (!isnan(root) && !isinf(root)) {
                double nearest = find_nearest_known_root(root);
                double error = fabs(root - nearest);

                strcpy(results[result_count].method_name, method_names[method]);
                results[result_count].root = root;
                results[result_count].iterations = iterations;
                results[result_count].func_calls = func_calls;
                results[result_count].time_ms = time_ms;
                results[result_count].error = error;
                result_count++;

                printf("%-20s %-12.6f %-8d %-10d %-10.3f %-10.2e\n",
                       method_names[method], root, iterations, func_calls, time_ms, error);
            }
        }
    }

    FILE *fp = fopen("results.csv", "w");
    fprintf(fp, "Method,Root,Iterations,FuncCalls,Time,Error\n");
    for (int i = 0; i < result_count; i++) {
        fprintf(fp, "%s,%.8f,%d,%d,%.6f,%.2e\n",
                results[i].method_name, results[i].root, results[i].iterations,
                results[i].func_calls, results[i].time_ms, results[i].error);
    }
    fclose(fp);

    FILE *gp = fopen("plot_results.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'comparison_results.png'\n");
    fprintf(gp, "set multiplot layout 2,2\n");
    fprintf(gp, "\n");

    fprintf(gp, "set title 'Iterations Comparison'\n");
    fprintf(gp, "set xlabel 'Method'\n");
    fprintf(gp, "set ylabel 'Average Iterations'\n");
    fprintf(gp, "set style data histograms\n");
    fprintf(gp, "set style histogram clustered\n");
    fprintf(gp, "set style fill solid 0.7\n");
    fprintf(gp, "set xtics rotate by -45\n");
    fprintf(gp, "plot 'method_stats.dat' using 2:xtic(1) title 'Iterations' linecolor rgb '#1f77b4'\n");
    fprintf(gp, "\n");

    fprintf(gp, "set title 'Function Calls Comparison'\n");
    fprintf(gp, "set ylabel 'Average Function Calls'\n");
    fprintf(gp, "plot 'method_stats.dat' using 3:xtic(1) title 'Function Calls' linecolor rgb '#ff7f0e'\n");
    fprintf(gp, "\n");

    fprintf(gp, "set title 'Execution Time Comparison'\n");
    fprintf(gp, "set ylabel 'Average Time (ms)'\n");
    fprintf(gp, "plot 'method_stats.dat' using 4:xtic(1) title 'Time' linecolor rgb '#2ca02c'\n");
    fprintf(gp, "\n");

    fprintf(gp, "set title 'Accuracy Comparison'\n");
    fprintf(gp, "set ylabel 'Average Error'\n");
    fprintf(gp, "set logscale y\n");
    fprintf(gp, "plot 'method_stats.dat' using 5:xtic(1) title 'Error' linecolor rgb '#d62728'\n");
    fprintf(gp, "\n");
    fprintf(gp, "unset multiplot\n");
    fclose(gp);

    FILE *stats = fopen("method_stats.dat", "w");
    for (int method = 0; method < 6; method++) {
        int count = 0;
        double sum_iter = 0, sum_calls = 0, sum_time = 0, sum_error = 0;

        for (int i = 0; i < result_count; i++) {
            if (strstr(results[i].method_name, method_names[method]) != NULL) {
                sum_iter += results[i].iterations;
                sum_calls += results[i].func_calls;
                sum_time += results[i].time_ms;
                sum_error += results[i].error;
                count++;
            }
        }

        if (count > 0) {
            fprintf(stats, "%s %.1f %.1f %.3f %.2e\n", 
                   method_names[method], sum_iter/count, sum_calls/count,
                   sum_time/count, sum_error/count);
        }
    }
    fclose(stats);

    printf("\n결과 파일들이 생성되었습니다:\n");
    printf("- results.csv: 상세 결과\n");
    printf("- method_stats.dat: 방법별 통계\n");
    printf("- plot_results.gp: gnuplot 스크립트\n");
    printf("\ngnuplot으로 그래프를 생성하려면: gnuplot plot_results.gp\n");

    return 0;
}