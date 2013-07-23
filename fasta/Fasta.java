
import java.util.Date;
import java.util.HashMap;
import java.util.Vector;

public class Fasta
{
    static int last = 42;
    static final int A = 3877;
    static final int C = 29573;
    static final int M = 139968;

    static double rand(int max) {
      last = (last * A + C) % M;
      return max * last / (double)M;
    }

    static final String ALU =
      "GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGG" +
      "GAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGA" +
      "CCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAAT" +
      "ACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCA" +
      "GCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGG" +
      "AGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCC" +
      "AGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

    static HashMap<Character, Double> IUB = new HashMap<Character, Double>();
    static void InitializeIUB() {
        IUB.put('a', 0.27);
        IUB.put('c', 0.12);
        IUB.put('g', 0.12);
        IUB.put('t', 0.27);
        IUB.put('B', 0.02);
        IUB.put('D', 0.02);
        IUB.put('H', 0.02);
        IUB.put('K', 0.02);
        IUB.put('M', 0.02);
        IUB.put('N', 0.02);
        IUB.put('R', 0.02);
        IUB.put('S', 0.02);
        IUB.put('V', 0.02);
        IUB.put('W', 0.02);
        IUB.put('Y', 0.02);
    }

    static HashMap<Character, Double> HomoSap = new HashMap<Character, Double>();
    static void InitializeHomoSap() {
        HomoSap.put('a', 0.3029549426680);
        HomoSap.put('c', 0.1979883004921);
        HomoSap.put('g', 0.1975473066391);
        HomoSap.put('t', 0.3015094502008);
    }

    static void makeCumulative(HashMap<Character, Double> table) {
        char last = '\u0000';
        for (Character ch : table.keySet()) {
            char c = ch.charValue();
            if (last != '\u0000') {
                table.put(c, table.get(c).doubleValue() + table.get(last).doubleValue());
            }
            last = c;
        }
    }

    static volatile String ret = null;

    static void fastaRepeat(int n, String seq) {
        int seqi = 0;
        int lenOut = 60;
        while (n > 0) {
            if (n<lenOut) lenOut = n;
            if (seqi + lenOut < seq.length()) {
                ret = seq.substring(seqi, seqi+lenOut);
                seqi += lenOut;
            } else {
                String s = seq.substring(seqi);
                seqi = lenOut - s.length();
                ret = s + seq.substring(0, seqi);
            }
            n -= lenOut;
        }
    }

    static void fastaRandom(int n, HashMap<Character, Double> table) {
        char[] line = new char[60];
        makeCumulative(table);
        while (n>0) {
            if (n<line.length) line = new char[n];
            for (int i=0; i<line.length; i++) {
                double r = rand(1);
                for (Character ch : table.keySet()) {
                    char c = ch.charValue();
                    if (r < table.get(c).doubleValue()) {
                        line[i] = c;
                        break;
                    }
                }
            }
            ret = new String(line);
            n -= line.length;
        }
    }

    static void runFasta() {
        int count = 7;
        fastaRepeat(2*count*100000, ALU);
        fastaRandom(3*count*1000, IUB);
        fastaRandom(5*count*1000, HomoSap);
    }

    static public void main(String[] args) {
        InitializeIUB();
        InitializeHomoSap();
        Date d1 = new Date();
        for (int i = 0; i < 10; i++)
            runFasta();
        Date d2 = new Date();
        System.out.println("Java Time: " + ((d2.getTime() - d1.getTime()) / 1000.0) +
                           " (count=" + ret + ")");
    }
}
