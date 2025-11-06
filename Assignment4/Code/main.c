#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NRANSI
#include "nrutil.h"

#define select nrselect
#include "nr.h"
#undef select

#define NBIN 100

float ran1(long *idum);
float gasdev(long *idum);

float uniform_random(float a, float b, long *idum) {
    return a + (b - a) * ran1(idum);
}

float gaussian_random(float m, float s, long *idum) {
    return m + s * gasdev(idum);
}

void write_samples(const char *filename, float *samples, int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%.6f\n", samples[i]);
    }
    fclose(fp);
    printf("Samples written to %s\n", filename);
}

void generate_samples(int nsamples, float a, float b, float m, float s, long *seed) {
    float *uniform_samples = (float *)malloc(nsamples * sizeof(float));
    float *gaussian_samples = (float *)malloc(nsamples * sizeof(float));
    
    if (uniform_samples == NULL || gaussian_samples == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }
    
    for (int i = 0; i < nsamples; i++) {
        uniform_samples[i] = uniform_random(a, b, seed);
    }
    for (int i = 0; i < nsamples; i++) {
        gaussian_samples[i] = gaussian_random(m, s, seed);
    }
    
    char uniform_filename[50];
    char gaussian_filename[50];
    sprintf(uniform_filename, "uniform_%d.txt", nsamples);
    sprintf(gaussian_filename, "gaussian_%d.txt", nsamples);
    
    write_samples(uniform_filename, uniform_samples, nsamples);
    write_samples(gaussian_filename, gaussian_samples, nsamples);
    
    float uniform_mean = 0.0, gaussian_mean = 0.0;
    for (int i = 0; i < nsamples; i++) {
        uniform_mean += uniform_samples[i];
        gaussian_mean += gaussian_samples[i];
    }
    uniform_mean /= nsamples;
    gaussian_mean /= nsamples;
    
    float uniform_var = 0.0, gaussian_var = 0.0;
    for (int i = 0; i < nsamples; i++) {
        float diff_u = uniform_samples[i] - uniform_mean;
        float diff_g = gaussian_samples[i] - gaussian_mean;
        uniform_var += diff_u * diff_u;
        gaussian_var += diff_g * diff_g;
    }
    uniform_var /= nsamples;
    gaussian_var /= nsamples;
    
    printf("\n[N = %d]\n", nsamples);
    printf("Uniform distribution [%.1f, %.1f]:\n", a, b);
    printf("  Mean: %.4f (Expected: %.4f)\n", uniform_mean, (a + b) / 2.0);
    printf("  Variance: %.4f (Expected: %.4f)\n", uniform_var, (b - a) * (b - a) / 12.0);
    printf("Gaussian distribution (m=%.1f, s=%.1f):\n", m, s);
    printf("  Mean: %.4f (Expected: %.4f)\n", gaussian_mean, m);
    printf("  Variance: %.4f (Expected: %.4f)\n", gaussian_var, s * s);
    printf("\n");
    
    free(uniform_samples);
    free(gaussian_samples);
}

int main(void) {
    float a = -3.0;
    float b = 4.0;
    float m = 0.5;
    float s = 1.5;
    long seed = -12345;
    
    printf("==========================================================\n");
    printf("Random Number Generation - Homework #4\n");
    printf("==========================================================\n");
    printf("Parameters:\n");
    printf("  Uniform distribution: [%.1f, %.1f]\n", a, b);
    printf("  Gaussian distribution: mean=%.1f, std=%.1f\n", m, s);
    printf("  Histogram bins: %d\n", NBIN);
    printf("==========================================================\n\n");
    
    int sample_sizes[] = {100, 1000, 10000, 100000};
    int num_sizes = 4;
    
    for (int i = 0; i < num_sizes; i++) {
        generate_samples(sample_sizes[i], a, b, m, s, &seed);
    }
    
    printf("==========================================================\n");
    printf("All samples generated successfully!\n");
    printf("Run 'python histogram.py' to visualize the histograms.\n");
    printf("==========================================================\n");
    
    return 0;
}
