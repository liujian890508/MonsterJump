#ifndef __ADMANAGER_H__
#define __ADMANAGER_H__

#include "cocos2d.h"
#include "Singleton.h"
#include "TypeInfoDef.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
#include <jni.h>
#include "jni/JniHelper.h"
#include <android/log.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "YouMiUtil.h"
#endif

USING_NS_CC;

class AdManager: public Singleton<AdManager>
{
public:
	AdManager();
	~AdManager();

	void showBanner();
	void hideBanner();
	void showSpotAds();
	bool closeSpotAds();
	void showOffersWall();
	void showOffersWallDialog(int width = 0, int height = 0);
	int queryPoints();
	bool spendPoints(int amount);
	bool awardPoints(int amount);

	void resultRoute(int code);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	jobject getAppActivity();
	jobject getYouMiManager();
#endif
};

#define AdMgr AdManager::getInstance()

#endif