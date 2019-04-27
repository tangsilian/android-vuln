LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := msm_cameraconfig.c

LOCAL_MODULE := libmsm_cameraconfig_exploit

LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)
