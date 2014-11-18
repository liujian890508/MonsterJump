#include "HomeLayer.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "GameWorld.h"
#include "ShareManager.h"
#include "AdManager.h"
#include "Background.h"

HomeLayer::HomeLayer()
{
}


HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	this->loadResource();

	auto background = Background::create();
	this->addChild(background);

	auto playerMenu = MenuItemImage::create("ui/btn_play.jpg", "ui/btn_play.jpg", [=](Ref *pSender){
        std::tuple<int, std::string> param = std::make_tuple(12, "Hello World");
		Utils::replaceScene(GameWorld::create(), &param);
	});
	auto shareMenu = MenuItemImage::create("ui/btn_share.png", "ui/btn_share.png", [=](Ref* pSender){
        ShareMgr->setDefaultContent();
        ShareMgr->sendShare();
    });
	auto spotAds = MenuItemFont::create("SpotAds", [=](Ref* pSender){
		AdMgr->showSpotAds();
	});
	auto menu = Menu::create(playerMenu, shareMenu, spotAds, nullptr);
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
