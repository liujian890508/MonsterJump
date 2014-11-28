#include "Store.h"
#include "cocostudio\CCSGUIReader.h"
#include "ui\CocosGUI.h"
#include "Utils.h"
#include "VisibleRect.h"
#include "HomeLayer.h"
#include "BuyCoin.h"
using namespace cocostudio;


Store::Store()
{
}


Store::~Store()
{
}

bool Store::init()
{
	auto bgSprite = Sprite::create("ui/ui_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	auto rect = VisibleRect::getVisibleRect();
	float scaleX = rect.size.width / bgSprite->getContentSize().width;
	float scaleY = rect.size.height / bgSprite->getContentSize().height;
	bgSprite->setScaleX(scaleX);
	bgSprite->setScaleY(scaleY);

	auto widget = GUIReader::getInstance()->widgetFromJsonFile("ui/UI_Store.json");
	this->addChild(widget);
	widget->setAnchorPoint(Vec2(0.5f, 0.5f));
	widget->setPosition(VisibleRect::center());

	return this->initWithMenu();
}

bool Store::initWithMenu()
{
	auto closeMenu = MenuItemImage::create("ui/btn_back.png", "ui/btn_back.png", [=](Ref *pSender){
		Utils::replaceScene(HomeLayer::create());
	});
	auto menu = Menu::create(closeMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::leftTop() + Point(closeMenu->getContentSize().width / 2, -closeMenu->getContentSize().height / 2));
	return this->initCoin();
}

bool Store::initCoin()
{
	auto coinBuyMenu = MenuItemImage::create("ui/ui_coin_display.png", "ui/ui_coin_display.png", [=](Ref *pSender){
		std::tuple<LayerName> param = std::make_tuple(layer_Store);
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
