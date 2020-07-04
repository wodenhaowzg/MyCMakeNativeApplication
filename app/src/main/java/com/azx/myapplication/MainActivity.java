package com.azx.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.azx.jni.MyFirstJni;

public class MainActivity extends AppCompatActivity {

    private MyFirstJni mMyFirstJni;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initJni();
    }

    private void initJni() {
        mMyFirstJni = new MyFirstJni();
        mMyFirstJni.initialize(mMyFirstJni);
        mMyFirstJni.firstOneNativeMethod();
    }
}
