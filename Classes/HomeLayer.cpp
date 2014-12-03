#include "HomeLayer.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "GameWorld.h"
#include "ShareManager.h"
#include "AdManager.h"
#include "Background.h"
#include "Setting.h"
#include "Store.h"

HomeLayer::HomeLayer()
{
}


HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	this->setEntityType(kType_Home);
	this->setMessageEnabled(true);

	this->loadResource();

	auto background = Background::create();
	this->addChild(background);

	auto logoSprite = Sprite::create("ui/text_gametittle.png");
	this->addChild(logoSprite, 0, 10);
	logoSprite->setPosition(VisibleRect::center() + Point(0, 250));

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

	this->playLogoAni();

	this->initTest();

	return true;
}

static bool flag = false;
bool HomeLayer::initTest()
{
	int points = AdMgr->queryPoints();
	auto label = Label::createWithSystemFont("Score:" + std::to_string(points), "", 32);
	label->setPosition(Point(300, 250));
	this->addChild(label);

	auto testMenu = MenuItemFont::create("TestMenu", [=](Ref *pSender){
		if (!flag){
			CCLOG("--------------------------awardPoints");
			AdMgr->awardPoints(10);
			flag = true;
		}
		else {
			CCLOG("--------------------------awardPoints");
			AdMgr->awardPoints(10);
			flag = false;
		}
		int points = AdMgr->queryPoints();
		label->setString("Score:" + std::to_string(points));
	});
	auto menu = Menu::create(testMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(300, 200);
	return true;
}

bool HomeLayer::initOther()
{
	auto settingMenu = MenuItemImage::create("ui/btn_setting.png", "ui/btn_setting.png", [=](Ref* pSender){
		Utils::replaceScene(Setting::create());
	});
	auto otherMenu = MenuItemImage::create("ui/btn_menu.png", "ui/btn_menu.png", [=](Ref *pSender){
		Utils::replaceScene(Store::create());
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

bool HomeLayer::handleMessage(const Telegram &msg)
{
	CCLOG("-----------------------------------------------HomeLayer message handle");
	return true;
}

void HomeLayer::playLogoAni()
{
	auto logoSprite = this->getChildByTag(10);
	logoSprite->setScale(0.9f);
	auto seqAction = Sequence::create(
		ScaleTo::create(1.0f, 1.0f),
		ScaleTo::create(1.0f, 0.9f),
		nullptr);
	logoSprite->runAction(RepeatForever::create( seqAction));
}

bool HomeLayer::loadResource()
{
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("plist/player.plist", "plist/player.png");
	spriteFrameCache->addSpriteFramesWithFile("plist/bird.plist", "plist/bird.png");
	return true;
}
