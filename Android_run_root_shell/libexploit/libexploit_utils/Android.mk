LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  hack_addr_limit.c \
  protect_from_oom_killer.c \
  kernel_memory_by_pipe.c

LOCAL_MODULE := libexploit_utils
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)
