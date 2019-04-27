LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDFLAGS   += -llog
LOCAL_CFLAGS    += -DDEBUG
LOCAL_MODULE    := exploit
LOCAL_SRC_FILES := exploit.c

include $(BUILD_EXECUTABLE)


