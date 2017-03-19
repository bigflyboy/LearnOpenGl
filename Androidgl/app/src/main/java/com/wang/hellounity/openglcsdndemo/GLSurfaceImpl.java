package com.wang.hellounity.openglcsdndemo;

import android.content.res.AssetManager;

/**
 * Created by sj on 16/12/23.
 */
public class GLSurfaceImpl {
    static {
        System.loadLibrary("visionin");
    }

    public static native void initAsset(AssetManager am);

    public static native void onSurfaceCreated();

    public static native void onSurfaceChanged(int width, int height);

    public static native void onDrawFrame();

}
