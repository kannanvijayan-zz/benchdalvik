// The Great Computer Language Shootout
// http://shootout.alioth.debian.org/
//
// modified by Isaac Gouy
// ported to C by Kannan Vijayan

#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

double DoubleTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (((double)tv.tv_usec) / 1000000);
}

int nsieve(int m, bool *isPrime) {
    int i, k, count;

    for (i = 2; i <= m; i++) { isPrime[i] = true; }
    count = 0;

    for (i = 2; i <= m; i++) {
        if (isPrime[i]) {
            for (k = i + i; k <= m; k += i)
                isPrime[k] = false;
            count++;
        }
    }
    return count;
}

int sieve() {
    int count = 0;
    for (int i = 1; i <= 3; i++) {
        int m = (1 << i) * 10000;
        bool *flags = (bool*) malloc(sizeof(bool) * (m + 1));
        count += nsieve(m, flags);
        free(flags);
    }
    return count;
}

int main() {
    int count = 0;
    double d1 = DoubleTime();
    for (int i = 0; i < 1000; i++) {
        count += sieve();
    }
    double d2 = DoubleTime();
    fprintf(stderr, "CXX Time: %lf  (count=%d)\n", (d2 - d1), count);
    return 0;
}
