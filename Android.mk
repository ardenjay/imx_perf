LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := imx_perf.c

LOCAL_CFLAGS += -g
LOCAL_MULTILIB := both
LOCAL_MODULE := imx_perf
LOCAL_MODULE_STEM_32 := imx_perf32
LOCAL_MODULE_STEM_64 := imx_perf

LOCAL_MODULE_TAGS := debug

include $(BUILD_EXECUTABLE)

