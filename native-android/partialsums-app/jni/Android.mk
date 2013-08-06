LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := partial-sums
LOCAL_SRC_FILES := partial-sums.cc
LOCAL_ARM_MODE := arm
APP_OPTIM := release

include $(BUILD_SHARED_LIBRARY)
