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

	auto logoSprite = Sprite::create("ui/text_gametittle.png");
	this->addChild(logoSprite);
	logoSprite->setPosition(VisibleRect::center() + Point(0, 300));

	auto playerMenu = MenuItemImage::create("ui/btn_play.png", "ui/btn_play.png", [=](Ref *pSender){
        std::tuple<int, std::string> param = std::make_tuple(12, "Hello World");
		Utils::replaceScene(GameWorld::create(), &param);
	});

	auto menu = Menu::create(playerMenu, nullptr);
	this->addChild(menu);
	menu->setAnchorPoint(Vec2(0, 1));
	menu->setPosition(VisibleRect::center() + Point(0, -50));

	this->initOther();
	this->initRole();
	return true;
}

bool HomeLayer::initOther()
{
	auto settingMenu = MenuItemImage::create("ui/btn_setting.png", "ui/btn_setting.png", [=](Ref* pSender){
		
	});
	auto otherMenu = MenuItemImage::create("ui/btn_menu.png", "ui/btn_menu.png", [=](Ref *pSender){
		
	});
	auto menu = Menu::create(settingMenu, otherMenu, nullptr);
	menu->alignItemsHorizontallyWithPadding(30);
	this->addChild(menu);
	menu->setPosition(VisibleRect::leftTop() + Point(otherMenu->getContentSize().width + 30, 
		-otherMenu->getContentSize().height / 2 - 10));
	return true;
}

bool HomeLayer::initRole()
{
	auto heroSprite = Sprite::create("map/rabbit_walk_1.png");
	heroSprite->setAnchorPoint(Vec2(0.5, 0));
	Point currentPos = VisibleRect::leftBottom() + Point(heroSprite->getContentSize().width / 2, 150);
	Point targetPos = VisibleRect::rightBottom() + Point(-heroSprite->getContentSize().width / 2, 150);
	heroSprite->setPosition(currentPos);
	auto seqAction = Sequence::create(
		MoveTo::create(8.0f, targetPos),
		CallFuncN::create([=](Node *pSender){
			heroSprite->setFlippedX(true);
		}),
		MoveTo::create(8.0, currentPos),
		CallFuncN::create([=](Node *pSender){
			heroSprite->setFlippedX(false);
		}),
		nullptr);
	heroSprite->runAction(RepeatForever::create(seqAction));
	auto animate = Utils::getAnimate("rabbit_", 25, 35);
	heroSprite->runAction(RepeatForever::create( animate));
	this->addChild(heroSprite);
	return true;
}

bool HomeLayer::loadResource()
{
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("plist/player.plist", "plist/player.png");
	spriteFrameCache->addSpriteFramesWithFile("plist/bird.plist", "plist/bird.png");
	return true;
}
