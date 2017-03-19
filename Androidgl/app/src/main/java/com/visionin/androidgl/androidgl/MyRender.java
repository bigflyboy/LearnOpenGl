package com.visionin.androidgl.androidgl;

import android.opengl.GLSurfaceView;

import com.wang.hellounity.openglcsdndemo.GLSurfaceImpl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by sj on 16/12/23.
 */
public class MyRender implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        //gl.glClearColor(0.1f,1.0f,0.7f,0.5f);
        GLSurfaceImpl.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        //gl.glViewport(0,0,width,height);
        GLSurfaceImpl.onSurfaceChanged(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        //gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        GLSurfaceImpl.onDrawFrame();
    }
}
