#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"

#define NRANSI
#include "nr.h"
#undef fmin

void read_system(const char *fname, int *n, float ***A, float **b) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { perror(fname); exit(1); }
    fscanf(fp, "%d %d", n, n);
    *A = matrix(1, *n, 1, *n);
    *b = vector(1, *n);
    for (int i = 1; i <= *n; i++)
        for (int j = 1; j <= *n; j++) {
            double tmp; fscanf(fp, "%lf", &tmp);
            (*A)[i][j] = (float)tmp;
        }
    for (int i = 1; i <= *n; i++) {
        double tmp; fscanf(fp, "%lf", &tmp);
        (*b)[i] = (float)tmp;
    }
    fclose(fp);
}

void compute_inverse(float **Aorig, int n, float **invA) {
    int *indx = ivector(1, n);
    float d;
    float **A = matrix(1, n, 1, n);
    for (int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=Aorig[i][j];
    ludcmp(A, n, indx, &d);
    for (int j=1;j<=n;j++) {
        float *col = vector(1, n);
        for (int i=1;i<=n;i++) col[i]=0.0f;
        col[j]=1.0f;
        lubksb(A, n, indx, col);
        for (int i=1;i<=n;i++) invA[i][j]=col[i];
        free_vector(col,1,n);
    }
    free_ivector(indx,1,n);
    free_matrix(A,1,n,1,n);
}

float compute_determinant(float **Aorig, int n) {
    int *indx = ivector(1, n);
    float d;
    float **A = matrix(1, n, 1, n);
    for (int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=Aorig[i][j];
    ludcmp(A, n, indx, &d);
    float det = d;
    for (int i=1;i<=n;i++) det *= A[i][i];
    free_ivector(indx,1,n);
    free_matrix(A,1,n,1,n);
    return det;
}

void compute_residual(float **A, float *b, float *x, int n, float *r) {
    for(int i=1;i<=n;i++){
        r[i]=b[i];
        for(int j=1;j<=n;j++) r[i]-=A[i][j]*x[j];
    }
}

float vector_norm(float *v, int n){
    float s=0; for(int i=1;i<=n;i++) s+=v[i]*v[i];
    return sqrtf(s);
}

int main(void) {
    char fname[32];
    for (int idx = 1; idx <= 3; idx++) {
        int n;
        float **A, *b;
        sprintf(fname, "lineq%d.dat", idx);
        read_system(fname, &n, &A, &b);

        printf("=== System %d (n=%d) ===\n", idx, n);

        float det = compute_determinant(A, n);
        
        if (fabsf(det) < 1e-7f) {
            printf("Gauss-Jordan Elimination:\nMatrix is singular (det=%e), skipping\n", det);
        } else {
            float **Aj = matrix(1, n, 1, n);
            float **Bj = matrix(1, n, 1, 1);
            for(int i=1;i<=n;i++){
                for(int j2=1;j2<=n;j2++) Aj[i][j2]=A[i][j2];
                Bj[i][1]=b[i];
            }
            gaussj(Aj, n, Bj, 1);
            printf("Gauss-Jordan Elimination:\n");
            for(int i=1;i<=n;i++) printf("%.6f\t\t", Bj[i][1]);
            printf("\n");
            free_matrix(Aj,1,n,1,n);
            free_matrix(Bj,1,n,1,1);
        }

        float **Alu = matrix(1,n,1,n);
        float *xlu = vector(1,n);
        int *indx = ivector(1,n);
        for(int i=1;i<=n;i++){
            for(int j2=1;j2<=n;j2++) Alu[i][j2]=A[i][j2];
            xlu[i]=b[i];
        }
        float dsign;
        ludcmp(Alu, n, indx, &dsign);
        lubksb(Alu, n, indx, xlu);
        printf("LU Decomposition:\n");
        for(int i=1;i<=n;i++) printf("%.6f\t\t", xlu[i]);
        printf("\n");

        float **Asvd = matrix(1,n,1,n);
        float *w = vector(1,n);
        float **V = matrix(1,n,1,n);
        float *xsvd = vector(1,n);
        for(int i=1;i<=n;i++){
            for(int j2=1;j2<=n;j2++) Asvd[i][j2]=A[i][j2];
            xsvd[i]=0.0f;
        }
        svdcmp(Asvd, n, n, w, V);
        float wmax=0, wmin=1e30f;
        for(int j2=1;j2<=n;j2++){
            if(w[j2]>wmax) wmax=w[j2];
            if(w[j2]>0 && w[j2]<wmin) wmin=w[j2];
        }
        for(int j2=1;j2<=n;j2++){
            float sum=0;
            if(w[j2]>wmax*1e-6f){
                for(int i=1;i<=n;i++) sum += Asvd[i][j2]*b[i];
                sum /= w[j2];
            }
            for(int i=1;i<=n;i++) xsvd[i]+=V[i][j2]*sum;
        }
        printf("SV Decomposition:\n");
        for(int i=1;i<=n;i++) printf("%.6f\t\t", xsvd[i]);
        printf("\n");

        float *rlu = vector(1,n);
        for(int it=1; it<=3; it++){
            mprove(A, Alu, n, indx, b, xlu);
        }
        printf("Iterative Improvement:\n");
        for(int i=1;i<=n;i++) printf("%.6f\t\t", xlu[i]);
        printf("\n");
        free_vector(rlu,1,n);

        float **invA = matrix(1,n,1,n);
        compute_inverse(A,n,invA);
        printf("Inverse Matrix:\n");
        for(int i=1;i<=n;i++){
            for(int j2=1;j2<=n;j2++){
                printf("%.5f ", invA[i][j2]);
            }
            printf("\n");
        }

        printf("Determinant:\n");
        printf("%.6f\n", det);

        free_matrix(A,1,n,1,n);
        free_vector(b,1,n);
        free_matrix(Alu,1,n,1,n);
        free_vector(xlu,1,n);
        free_ivector(indx,1,n);
        free_matrix(Asvd,1,n,1,n);
        free_vector(w,1,n);
        free_matrix(V,1,n,1,n);
        free_vector(xsvd,1,n);
        free_matrix(invA,1,n,1,n);

        printf("\n");
    }
    return 0;
}
