LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  poc.c \
  getroot.c

LOCAL_CFLAGS += -DDEBUG -D__ARM__ -Wunused

LOCAL_MODULE := poc
LOCAL_MODULE_TAGS := optional
LOCAL_LDFLAGS += -static

include $(BUILD_EXECUTABLE)
