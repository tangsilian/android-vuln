LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  kallsyms_in_memory.c \

LOCAL_MODULE := libkallsyms
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)
