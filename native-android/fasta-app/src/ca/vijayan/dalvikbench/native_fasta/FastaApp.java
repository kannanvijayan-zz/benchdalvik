package ca.vijayan.dalvikbench.native_fasta;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class FastaApp extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        TextView text = (TextView) findViewById(R.id.text);
        double time = runBench();
        text.setText("Dalvik Native Time=" + time);
    }

    public native double runBench();

    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("fasta");
    }
}
