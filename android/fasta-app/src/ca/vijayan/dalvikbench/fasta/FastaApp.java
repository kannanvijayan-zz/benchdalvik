package ca.vijayan.dalvikbench.fasta;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import java.util.Date;

public class FastaApp extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        TextView text = (TextView) findViewById(R.id.text);
        String[] result = new String[1];
        double time = Fasta.main(result);
        text.setText("Dalvik Time=" + time + " (count=" + result[0] + ")");
    }
}
