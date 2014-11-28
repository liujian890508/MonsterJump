#include "Setting.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "HomeLayer.h"
#include "BuyCoin.h"
using namespace ui;
using namespace cocostudio;

Setting::Setting()
{
}


Setting::~Setting()
{
}

bool Setting::init()
{
	auto bgSprite = Sprite::create("ui/ui_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	auto rect = VisibleRect::getVisibleRect();
	float scaleX = rect.size.width / bgSprite->getContentSize().width;
	float scaleY = rect.size.height / bgSprite->getContentSize().height;
	bgSprite->setScaleX(scaleX);
	bgSprite->setScaleY(scaleY);

	auto widget = GUIReader::getInstance()->widgetFromJsonFile("ui/UI_Setting.json");
	widget->setPosition(VisibleRect::center());
	widget->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(widget);

	Button *btnRank = static_cast<Button*>(widget->getChildByName("Button_4"));
	Button *rateUs = static_cast<Button*>(widget->getChildByName("Button_3"));
	Button *achivement = static_cast<Button*>(widget->getChildByName("Button_5"));

	btnRank->addClickEventListener([=](Ref * sender) {
		CCLOG("-------------------------------------------1");
	});

	rateUs->addClickEventListener([=](Ref *sender){
		CCLOG("-------------------------------------------2");
	});

	achivement->addClickEventListener([=](Ref *sender){
		CCLOG("-------------------------------------------3");
	});

	LoadingBar *music = static_cast<LoadingBar*>(widget->getChildByName("ProgressBar_11"));
	LoadingBar *sound = static_cast<LoadingBar*>(widget->getChildByName("ProgressBar_11_0"));

	music->setPercent(100);
	sound->setPercent(50);

	return this->initWithMenu();
}
 
bool Setting::initWithMenu()
{
	auto closeMenu = MenuItemImage::create("ui/btn_back.png", "ui/btn_back.png", [=](Ref *pSender){
		Utils::replaceScene(HomeLayer::create());
	});
	auto menu = Menu::create(closeMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::leftTop() + Point(closeMenu->getContentSize().width / 2, -closeMenu->getContentSize().height /2));
	return this->initCoin();
}

bool Setting::initCoin()
{
	auto coinBuyMenu = MenuItemImage::create("ui/ui_coin_display.png", "ui/ui_coin_display.png", [=](Ref *pSender){
		std::tuple<LayerName> param = std::make_tuple(layer_Setting);
		Utils::replaceScene(BuyCoin::create(), &param);
	});
	auto menu = Menu::create(coinBuyMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::rightTop() - Point(coinBuyMenu->getContentSize().width / 2 - 10,
		coinBuyMenu->getContentSize().height / 2 + 20));

	std::string coin = Utils::getItem("coin");
	if (coin == "") coin = "0";
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 30);
	auto coinLabel = Label::createWithTTF(ttfConfig, coin.c_str());
	coinLabel->setAlignment(TextHAlignment::LEFT);
	coinBuyMenu->addChild(coinLabel);
	coinLabel->setPosition(Point(coinBuyMenu->getContentSize() / 2));

	return true;
}
