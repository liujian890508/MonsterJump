#include "BuyCoin.h"
#include "cocostudio\CCSGUIReader.h"
#include "ui\CocosGUI.h"
#include "Utils.h"
#include "VisibleRect.h"
#include "Setting.h"
#include "Store.h"
using namespace cocostudio;
using namespace ui;

BuyCoin::BuyCoin()
{
	this->_fromLayer = layer_none;
}


BuyCoin::~BuyCoin()
{
}

bool BuyCoin::init()
{
	this->initBackground();

	auto widget = GUIReader::getInstance()->widgetFromJsonFile("ui/UI_IAP.json");
	this->addChild(widget);
	widget->setPosition(VisibleRect::center());
	widget->setAnchorPoint(Vec2(0.5f, 0.5f));
	return this->initWithMenu();
}

bool BuyCoin::initBackground()
{
	auto bgSprite = Sprite::create("ui/ui_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	auto rect = VisibleRect::getVisibleRect();
	float scaleX = rect.size.width / bgSprite->getContentSize().width;
	float scaleY = rect.size.height / bgSprite->getContentSize().height;
	bgSprite->setScaleX(scaleX);
	bgSprite->setScaleY(scaleY);
	return true;
}

bool BuyCoin::initWithMenu()
{
	auto closeMenu = MenuItemImage::create("ui/btn_back.png", "ui/btn_back.png", [=](Ref *pSender){
		switch (this->_fromLayer)
		{
		case layer_Store:
			Utils::replaceScene(Store::create());
			break;
		case layer_Setting:
			Utils::replaceScene(Setting::create());
			break;
		}
	});
	auto menu = Menu::create(closeMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::leftTop() + Point(closeMenu->getContentSize().width / 2, -closeMenu->getContentSize().height / 2));
	return this->initCoin();
}

bool BuyCoin::initCoin()
{
	auto coinBuyMenu = MenuItemImage::create("ui/ui_coin_display.png", "ui/ui_coin_display.png", [=](Ref *pSender){
		//Utils::replaceScene(BuyCoin::create());
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

bool BuyCoin::databind(void *data)
{
	std::tie(_fromLayer) = *static_cast<std::tuple<LayerName>*>(data);
	return true;
}