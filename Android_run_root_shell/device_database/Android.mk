DEVICE_DATABASE_LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(DEVICE_DATABASE_LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  device_database.c

LOCAL_MODULE := libdevice_database
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libsqlite

LOCAL_STATIC_LIBRARIES += libsqlite

include $(BUILD_STATIC_LIBRARY)

include $(DEVICE_DATABASE_LOCAL_PATH)/libsqlite/Android.mk

device.db:
	rm -f device.db
	sqlite3 $(DEVICE_DATABASE_LOCAL_PATH)/device.db < $(DEVICE_DATABASE_LOCAL_PATH)/db_init.sql

#WANTED_INSTALLED_MODULES += device.db
