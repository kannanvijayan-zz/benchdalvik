package ca.vijayan.dalvikbench.nsieve;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import java.util.Date;

public class NSieve extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        TextView text = (TextView) findViewById(R.id.text);
        int[] result = new int[1];
        double time = run(result);
        text.setText("Dalvik Time=" + time + " (count=" + result[0] + ")");
    }

    private static int nsieve(int m, boolean[] isPrime) {
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

    private static int sieve() {
        int count = 0;
        for (int i = 1; i <= 3; i++) {
            int m = (1 << i) * 10000;
            boolean[] flags = new boolean[m + 1];
            count += nsieve(m, flags);
        }
        return count;
    }

    private static double run(int[] result) {
        Date d1 = new Date();
        int count = 0;
        for (int i = 0; i < 100; i++)
            count += sieve();
        Date d2 = new Date();
        result[0] = count;
        return (d2.getTime() - d1.getTime()) / 1000.0;
    }
}
