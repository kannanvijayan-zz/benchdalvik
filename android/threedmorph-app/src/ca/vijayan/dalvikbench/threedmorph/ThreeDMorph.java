// The Great Computer Language Shootout
// http://shootout.alioth.debian.org/
// contributed by Isaac Gouy
// ported to Java by Kannan Vijayan

package ca.vijayan.dalvikbench.threedmorph;

import java.util.Date;

public class ThreeDMorph
{
    static final int loops = 15;
    static final int nx = 120;
    static final int nz = 120;

    static void morph(double[] a, double f) {
        double PI2nx = Math.PI * 8.0 / nx;
        double f30 = -(50 * Math.sin(f*Math.PI*2));

        for (int i = 0; i < nz; ++i) {
            for (int j = 0; j < nx; ++j) {
                a[3*(i*nx+j)+1] = Math.sin((j-1)*PI2nx) * -f30;
            }
        }
    }

    static double runMorph() {
        double[] a = new double[nx*nz*3];
        for (int i = 0; i < (nx*nz*3); ++i)
            a[i] = 0.0;

        for (int i = 0; i < loops; ++i)
            morph(a, i/(double)loops);

        double testOutput = 0.0;
        for (int i = 0; i < nx; i++) {
            testOutput += a[3*(i*nx+i)+1];
        }
        return testOutput;
    }

    public static double main(double[] result) {
        double count = 0;
        Date d1 = new Date();
        for (int i = 0; i < 100; i++)
            count += runMorph();
        Date d2 = new Date();
        result[0] = count;
        return (d2.getTime() - d1.getTime());
    }
}
