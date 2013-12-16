LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_FEATURES += exceptions

LOCAL_MODULE := main

SDL_PATH := ../SDL

SDL_GFX_PATH := ../SDL_gfx

SDL_IMAGE_PATH := ../SDL2_image

SDL_MIXER_PATH := ../SDL2_mixer

YAMLCPP_PATH := ../yamlcpp

BOOST_PATH := ../boost

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(SDL_GFX_PATH) \
	$(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
	$(LOCAL_PATH)/$(SDL_MIXER_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(subst $(LOCAL_PATH)/,, \
	$(LOCAL_PATH)/../../../src/main.cpp \
	$(LOCAL_PATH)/../../../src/lodepng.cpp \
	$(wildcard $(LOCAL_PATH)/../../../src/Basescape/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Battlescape/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Engine/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Engine/Scalers/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Geoscape/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Interface/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Menu/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Resource/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Ruleset/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Savegame/*.cpp) \
	$(wildcard $(LOCAL_PATH)/../../../src/Ufopaedia/*.cpp))

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL_gfx

LOCAL_LDLIBS := -lGLESv1_CM -llog

# yaml-cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(YAMLCPP_PATH)/include \
					$(LOCAL_PATH)/$(BOOST_PATH)/include
LOCAL_SRC_FILES += \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/$(YAMLCPP_PATH)/src/*.cpp))

include $(BUILD_SHARED_LIBRARY)
