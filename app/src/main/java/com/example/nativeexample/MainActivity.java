package com.example.nativeexample;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.media.AudioManager;
import android.media.AudioDeviceInfo;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

import com.example.nativeexample.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private boolean recording = false;
    private static final String TAG = "NativeExample";

    private ActivityMainBinding binding;

    public void recordClick(android.view.View v)
    {
        Log.w(TAG, "record button is clicked");

        if (!recording) {
            boolean result = jniStartRecording();
            if (result == true) Log.w(TAG, "Started recording");
            else Log.w(TAG, "Failed to start recording");

            recording = true;
        }

        for (int i = 0; i < 3; i++)
        {
//            int[] samples = getSamples(100);

//            Log.w(TAG, "10th sample: " + samples[10]);
        }
    }

    public void stopClick(android.view.View v)
    {
        Log.w(TAG, "stop button is clicked");

        if (recording) {
            jniStopRecording();
            recording = false;
        }
    }



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;

        StringBuilder sb = new StringBuilder();
        sb.append(stringFromJNI());
        sb.append(" = ");
//        int[] data = getArr();
//        for (int i: data)
//            sb.append(i);

        AudioManager am = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
        AudioDeviceInfo[] infos = am.getDevices(0x00000001);

//        for (AudioDeviceInfo adi: infos)
//        {
//            adi.
//        }


        String str = sb.toString();

        tv.setText(str);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int[] getArr();

    public native boolean jniStartRecording();
    public native boolean jniStopRecording();
    public native boolean jniClearStream();
    public native int[] jniGetSamples(int n_samples);


}