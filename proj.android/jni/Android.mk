LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Dialog.cpp \
				   ../../Classes/DialogManager.cpp \
				   ../../Classes/GameMap.cpp \
				   ../../Classes/GameUI.cpp \
				   ../../Classes/GameWorld.cpp \
				   ../../Classes/HomeLayer.cpp \
				   ../../Classes/ShareManager.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/Utils.cpp \
				   ../../Classes/VisibleRect.cpp \
				   ../../Classes/HeroSprite.cpp \
				   ../../Classes/NormalWall.cpp \
				   ../../Classes/GameLogic.cpp \
				   ../../Classes/Collapsar.cpp \
				   ../../Classes/ObjectManager.cpp \
				   ../../Classes/Plane.cpp \
				   ../../Classes/Bird.cpp \
				   ../../Classes/Gold.cpp \
				   ../../Classes/Background.cpp \
				   ../../Classes/Spring.cpp \
				   ../../Classes/AdManager.cpp \
				   ../../Classes/C2DXShareSDK/Android/JSON/cJSON/cJSON.c \
				   ../../Classes/C2DXShareSDK/Android/JSON/CCJSONConverter.cpp \
				   ../../Classes/C2DXShareSDK/Android/ShareSDKUtils.cpp \
				   ../../Classes/C2DXShareSDK/C2DXShareSDK.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/C2DXShareSDK/Android/JSON/cJSON

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
