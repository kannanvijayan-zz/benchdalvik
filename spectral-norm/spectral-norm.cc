
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double DoubleTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (((double)tv.tv_usec) / 1000000);
}

double A(int i, int j) {
  return ((double)1.0)/((i+j)*(i+j+1)/((double)(2+i+1)));
}

void Au(double *u, double *v, int length) {
  for (int i=0; i<length; ++i) {
    double t = 0;
    for (int j=0; j<length; ++j)
      t += A(i,j) * u[j];
    v[i] = t;
  }
}

void Atu(double *u, double *v, int length) {
  for (int i=0; i<length; ++i) {
    double t = 0;
    for (int j=0; j<length; ++j)
      t += A(j,i) * u[j];
    v[i] = t;
  }
}

void AtAu(double *u, double *v, double *w, int length) {
  Au(u, w, length);
  Atu(w, v, length);
}

double spectralnorm(int n) {
    int i;
    double *u = (double*)malloc(sizeof(double) * n);
    double *v = (double*)malloc(sizeof(double) * n);
    double *w = (double*)malloc(sizeof(double) * n);
    double vv = 0.0;
    double vBv = 0.0;

    for (i=0; i<n; ++i) {
        u[i] = 1; v[i] = w[i] = 0;
    }

    for (i=0; i<10; ++i) {
        AtAu(u,v,w,n);
        AtAu(v,u,w,n);
    }

   for (i=0; i<n; ++i) {
        vBv += u[i]*v[i];
        vv  += v[i]*v[i];
    }
    free(u);
    free(v);
    free(w);
    return sqrt(vBv/vv);
}

double runSpectralNorm() {
    double result = 0;
    for (int i = 6; i <= 48; i *= 2) {
        result += spectralnorm(i);
    }
    return result;
}

int main() {
    double count = 0;
    double d1 = DoubleTime();
    for (int i = 0; i < 500; i++) {
        count += runSpectralNorm();
    }
    double d2 = DoubleTime();
    fprintf(stderr, "CXX Time: %lf  (count=%lf)\n", (d2 - d1), count);
    return 0;
}
