#include "HomeLayer.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "GameWorld.h"

HomeLayer::HomeLayer()
{
}


HomeLayer::~HomeLayer()
{
}

bool HomeLayer::init()
{
	this->loadResource();

	CCLOG("welcome to HomeLayer");
	auto enterMenu = MenuItemFont::create("Play", [=](Ref *pSender){
		std::tuple<int, std::string> info = std::make_tuple(5, "hello world");
		Utils::replaceScene(GameWorld::create(), &info);
	});
	auto menu = Menu::create(enterMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::center());

	return true;
}

bool HomeLayer::loadResource()
{

	return true;
}
