LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := diag.c

LOCAL_MODULE := libdiagexploit

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_LIBRARIES := libdevice_database

include $(BUILD_STATIC_LIBRARY)
