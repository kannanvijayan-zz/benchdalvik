// The Great Computer Language Shootout
// http://shootout.alioth.debian.org/
// contributed by Isaac Gouy
// ported to Java by Kannan Vijayan

import java.util.Date;

public class PartialSums
{
    static double a2 = 0.0, a3 = 0.0, a4 = 0.0, a5 = 0.0, a6 = 0.0, a7 = 0.0, a8 = 0.0, a9 = 0.0;
    static int k3 = 0;
    static double sk = 0.0, ck = 0.0;

    public static double partial(int n) {
        double a1 = (a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = 0.0);
        double twothirds = 2.0/3.0;
        double alt = -1.0;
        int k2 = (k3 = 0);
        double sk = (ck = 0.0);
        
        for (int k = 1; k <= n; k++){
            k2 = k*k;
            k3 = k2*k;
            sk = Math.sin(k);
            ck = Math.cos(k);
            alt = -alt;
            
            a1 += Math.pow(twothirds,k-1);
            a2 += Math.pow(k,-0.5);
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

    public static double runPartial() {
        double result = 0;
        for (int i = 1024; i <= 16384; i *= 2) {
            result += partial(i);
        }
        return result;
    }

    public static void main(String[] args) {
        double count = 0;
        Date d1 = new Date();
        for (int i = 0; i < 100; i++)
            count += runPartial();
        Date d2 = new Date();
        System.out.println("Java Time: " + ((d2.getTime() - d1.getTime()) / 1000.0) +
                           " (count=" + count + ")");
    }
}
