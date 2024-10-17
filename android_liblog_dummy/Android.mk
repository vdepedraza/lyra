LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := log
LOCAL_SRC_FILES := log.cpp
include $(BUILD_STATIC_LIBRARY)
