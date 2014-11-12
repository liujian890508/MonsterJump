#include "HomeLayer.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "GameWorld.h"
#include "ShareManager.h"
#include "AdManager.h"

HomeLayer::HomeLayer()
{
}


HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	this->loadResource();

	auto enterMenu = MenuItemFont::create("Play", [=](Ref *pSender){
        std::tuple<int, std::string> param = std::make_tuple(12, "Hello World");
		Utils::replaceScene(GameWorld::create(), &param);
	});
    auto shareMenu = MenuItemFont::create("Share", [=](Ref* pSender){
        ShareMgr->setDefaultContent();
        ShareMgr->sendShare();
    });
	auto spotAds = MenuItemFont::create("SpotAds", [=](Ref* pSender){
		AdMgr->showSpotAds();
	});
	auto menu = Menu::create(enterMenu, shareMenu, spotAds, nullptr);
    menu->alignItemsVerticallyWithPadding(30);
	this->addChild(menu);
	menu->setPosition(VisibleRect::center());
	return true;
}

bool HomeLayer::loadResource()
{
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("player/player.plist", "player/player.png");
	return true;
}
