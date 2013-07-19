// The Great Computer Language Shootout
// http://shootout.alioth.debian.org/
//
// modified by Isaac Gouy
// ported to Java by Kannan Vijayan

import java.util.Date;

public class NSieve
{
    public static int nsieve(int m, boolean[] isPrime) {
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

    public static int sieve() {
        int count = 0;
        for (int i = 1; i <= 3; i++) {
            int m = (1 << i) * 10000;
            boolean[] flags = new boolean[m + 1];
            count += nsieve(m, flags);
        }
        return count;
    }

    public static void main(String[] args) {
        Date d1 = new Date();
        int count = 0;
        for (int i = 0; i < 1000; i++)
            count += sieve();
        Date d2 = new Date();
        System.out.println("Java Time: " + ((d2.getTime() - d1.getTime()) / 1000.0) +
                           " (count=" + count + ")");
    }
}
