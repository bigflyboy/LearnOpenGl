package com.visionin.androidgl.androidgl;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by sj on 16/12/23.
 */
public class MyGLSurface extends GLSurfaceView {

    MyRender mMyRender;

    public MyGLSurface(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        mMyRender = new MyRender();
        setRenderer(mMyRender);
    }

}
