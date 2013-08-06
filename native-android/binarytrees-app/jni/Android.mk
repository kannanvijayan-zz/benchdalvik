LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := binary-trees
LOCAL_SRC_FILES := binary-trees.cc
LOCAL_ARM_MODE := arm
APP_OPTIM := release

include $(BUILD_SHARED_LIBRARY)
