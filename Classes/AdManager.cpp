#include "AdManager.h"
#include "MessageDispatcher.h"

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

	void Java_com_xiandiao_jump_YouMiManager_pointsBalanceChange( JNIEnv *env,jobject thiz,jint points )
	{
		AdMgr->pointsBalanceChange(points);
	}
}

jobject AdManager::getYouMiManager()
{
	JniMethodInfo minfo;
	jobject jobj;
	bool b = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getYouMiManager", "()Ljava/lang/Object;");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}
	return jobj;
}

jobject AdManager::getAppActivity()
{
	JniMethodInfo minfo;
	jobject jobj;
	bool b = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Ljava/lang/Object;");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}
	return jobj;
}

#endif

void AdManager::showBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "showBanner", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	
#endif
}

void AdManager::hideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "hideBanner", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

bool AdManager::closeSpotAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "closeSpotAd", "()Z");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}
	else{
		jboolean flag = minfo.env->CallBooleanMethod(jobj, minfo.methodID);
		minfo.env->DeleteLocalRef(minfo.classID);
		return (bool)flag;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
	return false;
}

void AdManager::showSpotAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "showSpotAds", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
		minfo.env->DeleteLocalRef( minfo.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    YouMiUtil::showSpot();
#endif
}

void AdManager::showOffersWall()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "showOffersWall", "()V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}
	else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID);
		minfo.env->DeleteLocalRef( minfo.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    YouMiUtil::showOffers(true);
#endif
}

void AdManager::showOffersWallDialog(int width, int height)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jobject jobj = this->getYouMiManager();
	bool b = JniHelper::getMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "showOffersWallDialog", "(II)V");
	if (!b){
		CCLOG("JniHelper::getMethodInfo error...");
	}
	else{
		minfo.env->CallVoidMethod(jobj, minfo.methodID, width, height);
		minfo.env->DeleteLocalRef( minfo.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

int AdManager::queryPoints()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool b = JniHelper::getStaticMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "queryPoints", "()I");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		jint points = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
		return (int) points;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return YouMiUtil::getYouMiScore();
#endif
	return 0;
}

bool AdManager::spendPoints(int amount)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool b = JniHelper::getStaticMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "spendPoints", "(I)Z");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		jboolean flag = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID,amount);
		minfo.env->DeleteLocalRef(minfo.classID);
		return (bool)flag;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return YouMiUtil::spendPoints(amount);
#endif
	return false;
}

bool AdManager::awardPoints(int amount)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool b = JniHelper::getStaticMethodInfo(minfo, "com/xiandiao/jump/YouMiManager", "awardPoints", "(I)Z");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		jboolean flag = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, amount);
		return (bool)flag;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
	return false;
}

void AdManager::pointsBalanceChange(int points)
{
	CCLOG("current Score: %d", points);
	MessageDis->DispatchMsg(0, 0, -1, kMsg_pointsChange, &points);
}

void AdManager::resultRoute(int code)
{
	switch (code)
	{
	case ads_adView_switch://广告切换
		break;
	case ads_adView_success://广告请求成功
		break;
	case ads_adView_failed://广告请求失败
		break;
	case ads_spot_success://广告展示成功
		break;
	case ads_spot_failed://广告展示失败
		break;
	case ads_spot_closed://广告关闭
		break;
	case ads_offers_closed://积分广告关闭
		break;
	}
}
