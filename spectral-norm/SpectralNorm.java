
import java.util.Date;

public class SpectralNorm {

    static double A(int i, int j) {
      return ((double)1)/((i+j)*(i+j+1)/((double)2)+i+1);
    }

    static void Au(double[] u, double[] v) {
      for (int i=0; i<u.length; ++i) {
        double t = 0;
        for (int j=0; j<u.length; ++j)
          t += A(i,j) * u[j];
        v[i] = t;
      }
    }

    static void Atu(double[] u, double[] v) {
      for (int i=0; i<u.length; ++i) {
        double t = 0;
        for (int j=0; j<u.length; ++j)
          t += A(j,i) * u[j];
        v[i] = t;
      }
    }

    static void AtAu(double[] u, double[] v, double[] w) {
      Au(u, w);
      Atu(w, v);
    }

    static double spectralnorm(int n) {
        int i;
        double[] u = new double[n];
        double[] v = new double[n];
        double[] w = new double[n];
        double vv = 0.0;
        double vBv = 0.0;

        for (i=0; i<n; ++i) {
            u[i] = 1; v[i] = w[i] = 0;
        }

        for (i=0; i<10; ++i) {
            AtAu(u,v,w);
            AtAu(v,u,w);
        }

       for (i=0; i<n; ++i) {
            vBv += u[i]*v[i];
            vv  += v[i]*v[i];
        }
        return Math.sqrt(vBv/vv);
    }

    static double runSpectralNorm() {
        double result = 0;
        for (int i = 6; i <= 48; i *= 2) {
            result += spectralnorm(i);
        }
        return result;
    }

    public static void main(String[] args) {
        double count = 0;
        Date d1 = new Date();
        for (int i = 0; i < 500; i++)
            count += runSpectralNorm();
        Date d2 = new Date();
        System.out.println("Java Time: " + ((d2.getTime() - d1.getTime()) / 1000.0) +
                           " (count=" + count + ")");
    }
}
