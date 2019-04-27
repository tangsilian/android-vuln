MY_LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(MY_LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  exploit.c \
  mmap.c

LOCAL_MODULE := libexploit
LOCAL_MODULE_TAGS := optional
LOCAL_LDFLAGS += -static

TARGET_C_INCLUDES += \
  $(TOP_SRCDIR)/device_database \
  $(TOP_SRCDIR) \
  $(LOCAL_PATH)/libexploit_utils

LOCAL_C_INCLUDES += $(LOCAL_PATH)/libdiagexploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libperf_event_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libmsm_acdb_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libfj_hdcp_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libfb_mem_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libmsm_cameraconfig_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libput_user_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libget_user_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libpingpong_exploit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libfutex_exploit

LOCAL_STATIC_LIBRARIES += libdiagexploit
LOCAL_STATIC_LIBRARIES += libperf_event_exploit
LOCAL_STATIC_LIBRARIES += libmsm_acdb_exploit
LOCAL_STATIC_LIBRARIES += libfj_hdcp_exploit
LOCAL_STATIC_LIBRARIES += libfb_mem_exploit
LOCAL_STATIC_LIBRARIES += libmsm_cameraconfig_exploit
LOCAL_STATIC_LIBRARIES += libput_user_exploit
LOCAL_STATIC_LIBRARIES += libget_user_exploit
LOCAL_STATIC_LIBRARIES += libpingpong_exploit
LOCAL_STATIC_LIBRARIES += libfutex_exploit
LOCAL_STATIC_LIBRARIES += libexploit_utils

include $(BUILD_STATIC_LIBRARY)

include $(MY_LOCAL_PATH)/libdiagexploit/Android.mk
include $(MY_LOCAL_PATH)/libfb_mem_exploit/Android.mk
include $(MY_LOCAL_PATH)/libfj_hdcp_exploit/Android.mk
include $(MY_LOCAL_PATH)/libget_user_exploit/Android.mk
include $(MY_LOCAL_PATH)/libmsm_acdb_exploit/Android.mk
include $(MY_LOCAL_PATH)/libmsm_cameraconfig_exploit/Android.mk
include $(MY_LOCAL_PATH)/libperf_event_exploit/Android.mk
include $(MY_LOCAL_PATH)/libput_user_exploit/Android.mk
include $(MY_LOCAL_PATH)/libpingpong_exploit/Android.mk
include $(MY_LOCAL_PATH)/libfutex_exploit/Android.mk
include $(MY_LOCAL_PATH)/libexploit_utils/Android.mk
