LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := threedmorph
LOCAL_SRC_FILES := 3d-morph.cc
LOCAL_ARM_MODE := arm
APP_OPTIM := release

include $(BUILD_SHARED_LIBRARY)
