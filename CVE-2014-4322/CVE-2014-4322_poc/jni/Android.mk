LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= msm.c \
					shellcode.S

LOCAL_MODULE:= msdd 
#LOCAL_C_INCLUDES += $(common_includes) 
LOCAL_CPPFLAGS += -DDEBUG
LOCAL_CFLAGS += -DDEBUG
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog 

include $(BUILD_EXECUTABLE)
