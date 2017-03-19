LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_SRC_FILES	:=	\
com_wang_hellounity_openglcsdndemo_GLSurfaceImpl.cpp


LOCAL_LDLIBS    := -llog -lGLESv2 -lEGL -landroid -ljnigraphics

LOCAL_CFLAGS := -std=c++11

LOCAL_MODULE    := visionin

include $(BUILD_SHARED_LIBRARY)