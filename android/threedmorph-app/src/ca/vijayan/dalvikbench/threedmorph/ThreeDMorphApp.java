package ca.vijayan.dalvikbench.threedmorph;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import java.util.Date;

public class ThreeDMorphApp extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        TextView text = (TextView) findViewById(R.id.text);
        double[] result = new double[1];
        double time = ThreeDMorph.main(result);
        text.setText("Dalvik Time=" + time + " (count=" + result[0] + ")");
    }
}
