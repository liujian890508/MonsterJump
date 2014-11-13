#ifndef __ADMANAGER_H__
#define __ADMANAGER_H__

#include "cocos2d.h"
#include "Singleton.h"
#include "TypeInfoDef.h"
USING_NS_CC;

class AdManager: public Singleton<AdManager>
{
public:
	AdManager();
	~AdManager();

	void showSpotAds();

	void resultRoute(int code);
};

#define AdMgr AdManager::getInstance()

#endif