// The Great Computer Language Shootout
// http://shootout.alioth.debian.org/
// contributed by Isaac Gouy
// ported to C by Kannan Vijayan

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

volatile double a2 = 0.0, a3 = 0.0, a4 = 0.0, a5 = 0.0, a6 = 0.0, a7 = 0.0, a8 = 0.0, a9 = 0.0;
volatile double k3 = 0.0, sk = 0.0, ck = 0.0;

double partial(int n) {
    double a1 = (a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = 0.0);
    double twothirds = 2.0/3.0;
    double alt = -1.0;
    double k2 = (k3 = sk = ck = 0.0);
    
    for (int k = 1; k <= n; k++){
        k2 = k*k;
        k3 = k2*k;
        sk = sin(k);
        ck = cos(k);
        alt = -alt;
        
        a1 += pow(twothirds,k-1);
        a2 += pow(k,-0.5);
        a3 += 1.0/(k*(k+1.0));
        a4 += 1.0/(k3 * sk*sk);
        a5 += 1.0/(k3 * ck*ck);
        a6 += 1.0/k;
        a7 += 1.0/k2;
        a8 += alt/k;
        a9 += alt/(2*k -1);
    }
    return a1 + k2;
}

double run_partial() {
    double result = 0;
    for (int i = 1024; i <= 16384; i *= 2) {
        result += partial(i);
    }
    return result;
}

int main() {
    double count = 0;
    double d1 = DoubleTime();
    for (int i = 0; i < 1000; i++) {
        count += run_partial();
    }
    double d2 = DoubleTime();
    fprintf(stderr, "CXX Time: %lf  (count=%lf)\n", (d2 - d1), count);
    return 0;
}
