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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	void Java_org_cocos2dx_cpp_AppActivity_adsResultCallback(JNIEnv *env, jobject thiz, jint result)
	{
		AdMgr->resultRoute(result);
	}
}
#endif

void AdManager::showSpotAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj;
	bool b = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}else{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}
	b = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "showSpotAds", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

void AdManager::resultRoute(int code)
{
	switch (code)
	{
	case ads_adView_switch://����л�
		break;
	case ads_adView_success://�������ɹ�
		break;
	case ads_adView_failed://�������ʧ��
		break;
	case ads_spot_success://���չʾ�ɹ�
		break;
	case ads_spot_failed://���չʾʧ��
		break;
	case ads_spot_closed://���ر�
		break;
	}
}
