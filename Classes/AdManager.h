#ifndef __ADMANAGER_H__
#define __ADMANAGER_H__

#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;

class AdManager: public Singleton<AdManager>
{
public:
	AdManager();
	~AdManager();

	void showSpotAds();
};

#define AdMgr AdManager::getInstance()

#endif