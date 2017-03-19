package com.visionin.androidgl.androidgl;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.wang.hellounity.openglcsdndemo.GLSurfaceImpl;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
        GLSurfaceImpl.initAsset(getAssets());
        MyGLSurface myGLSurface = new MyGLSurface(getApplication());
        setContentView(myGLSurface);
    }
}
