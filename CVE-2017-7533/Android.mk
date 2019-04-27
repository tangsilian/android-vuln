LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := trigger.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_CFLAGS += -DDEBUG -D__ARM__ -Wunused

LOCAL_MODULE := main
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -std=c99
LOCAL_LDFLAGS += -static

include $(BUILD_EXECUTABLE)
