
#include <jni.h>
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

static const int loops = 15;
static const int nx = 120;
static const int nz = 120;

void morph(double *a, double f) {
    double PI2nx = M_PI * 8.0 / nx;
    double f30 = -(50 * sin(f*M_PI*2));

    for (int i = 0; i < nz; ++i) {
        for (int j = 0; j < nx; ++j) {
            a[3*(i*nx+j)+1] = sin((j-1)*PI2nx) * -f30;
        }
    }
}

double runMorph() {
    double *a = (double *) malloc(sizeof(double) * (nx*nz*3));
    for (int i = 0; i < (nx*nz*3); ++i) {
        a[i] = 0.0;
    }

    for (int i = 0; i < loops; ++i) {
        morph(a, i/(double)loops);
    }

    double testOutput = 0.0;
    for (int i = 0; i < nx; i++) {
        testOutput += a[3*(i*nx+i)+1];
    }
    free(a);
    return testOutput;
}


volatile static double storeResult = 0.0;

extern "C" {
jdouble
Java_ca_vijayan_dalvikbench_native_1threedmorph_ThreeDMorphApp_runBench( JNIEnv* env,
                                                  jobject thiz )
{
    double count = 0;
    double d1 = DoubleTime();
    for (int i = 0; i < 100; i++) {
        double result = runMorph();
        count += result;
    }
    double d2 = DoubleTime();
    storeResult = count;
    return (jdouble)(d2 - d1);
}
}
