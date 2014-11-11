#include "AdManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
#include <jni.h>
#include "jni/JniHelper.h"
#include <android/log.h>
#endif

AdManager::AdManager()
{
}


AdManager::~AdManager()
{
}

void AdManager::showSpotAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj;
	bool b = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp", "AppActivity", "()Ljava/lang/Object;");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}else{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}
	b = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp", "showSpotAds", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}
