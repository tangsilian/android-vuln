##
##
## Build the library
##
##

LOCAL_PATH:= $(call my-dir)

# NOTE the following flags,
#   SQLITE_TEMP_STORE=3 causes all TEMP files to go into RAM. and thats the behavior we want
#   SQLITE_ENABLE_FTS3   enables usage of FTS3 - NOT FTS1 or 2.
#   SQLITE_DEFAULT_AUTOVACUUM=1  causes the databases to be subject to auto-vacuum
common_sqlite_flags := \
	-DNDEBUG=1 \
	-DHAVE_USLEEP=1 \
	-DSQLITE_HAVE_ISNAN \
	-DSQLITE_DEFAULT_JOURNAL_SIZE_LIMIT=1048576 \
	-DSQLITE_THREADSAFE=2 \
	-DSQLITE_TEMP_STORE=3 \
	-DSQLITE_POWERSAFE_OVERWRITE=1 \
	-DSQLITE_DEFAULT_FILE_FORMAT=4 \
	-DSQLITE_DEFAULT_AUTOVACUUM=1 \
	-DSQLITE_ENABLE_MEMORY_MANAGEMENT=1 \
	-DSQLITE_ENABLE_FTS3 \
	-DSQLITE_ENABLE_FTS3_BACKWARDS \
	-DSQLITE_ENABLE_FTS4 \
	-DSQLITE_OMIT_BUILTIN_TEST \
	-DSQLITE_OMIT_COMPILEOPTION_DIAGS \
	-DSQLITE_OMIT_LOAD_EXTENSION \
	-DSQLITE_DEFAULT_FILE_PERMISSIONS=0600 \
	-Dfdatasync=fdatasync

common_src_files := sqlite3.c

ifeq ($(WITH_QC_PERF),true)
common_sqlite_flags += -DQC_PERF
endif

# the device library
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(common_src_files)

ifneq ($(TARGET_ARCH),arm)
LOCAL_LDLIBS += -lpthread -ldl
endif

LOCAL_CFLAGS += $(common_sqlite_flags) -DUSE_PREAD64 -Dfdatasync=fdatasync

LOCAL_SHARED_LIBRARIES := libdl

LOCAL_MODULE:= libsqlite
LOCAL_C_INCLUDES += $(call include-path-for, system-core)/cutils
LOCAL_SHARED_LIBRARIES += liblog \
            libicuuc \
            libicui18n \
            libutils \
            liblog

# include android specific methods
LOCAL_WHOLE_STATIC_LIBRARIES := libsqlite3_android

ifeq ($(WITH_QC_PERF),true)
LOCAL_WHOLE_STATIC_LIBRARIES += libqc-sqlite
LOCAL_SHARED_LIBRARIES += libcutils
endif

include $(BUILD_SHARED_LIBRARY)


ifeq ($(WITH_HOST_DALVIK),true)
    include $(CLEAR_VARS)
    LOCAL_SRC_FILES := $(common_src_files)
    LOCAL_LDLIBS += -lpthread -ldl
    LOCAL_CFLAGS += $(common_sqlite_flags)
    LOCAL_MODULE:= libsqlite
    LOCAL_SHARED_LIBRARIES += libicuuc libicui18n
    LOCAL_STATIC_LIBRARIES := liblog libutils libcutils

    # include android specific methods
    LOCAL_WHOLE_STATIC_LIBRARIES := libsqlite3_android
    include $(BUILD_HOST_SHARED_LIBRARY)
endif

##
##
## Build the device command line tool sqlite3
##
##
ifneq ($(SDK_ONLY),true)  # SDK doesn't need device version of sqlite3

include $(CLEAR_VARS)

LOCAL_SRC_FILES := shell.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../android $(call include-path-for, system-core)/cutils

LOCAL_SHARED_LIBRARIES := libsqlite \
            libicuuc \
            libicui18n \
            libutils

ifneq ($(TARGET_ARCH),arm)
LOCAL_LDLIBS += -lpthread -ldl
endif

LOCAL_CFLAGS += $(common_sqlite_flags) -DUSE_PREAD64

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)

LOCAL_MODULE_TAGS := debug

LOCAL_MODULE := sqlite3

include $(BUILD_EXECUTABLE)

endif # !SDK_ONLY


##
##
## Build the host command line tool sqlite3
##
##

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(common_src_files) shell.c

LOCAL_CFLAGS += $(common_sqlite_flags) -DNO_ANDROID_FUNCS=1

# sqlite3MemsysAlarm uses LOG()
LOCAL_STATIC_LIBRARIES += liblog

ifeq ($(strip $(USE_MINGW)),)
LOCAL_LDLIBS += -lpthread
ifneq ($(HOST_OS),freebsd)
LOCAL_LDLIBS += -ldl
endif
endif

LOCAL_MODULE := sqlite3

include $(BUILD_HOST_EXECUTABLE)
