LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  acdb.c \

LOCAL_MODULE := libmsm_acdb_exploit
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := device_database

include $(BUILD_STATIC_LIBRARY)
