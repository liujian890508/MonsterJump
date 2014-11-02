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

	auto enterMenu = MenuItemFont::create("Play", [=](Ref *pSender){
        std::tuple<int, std::string> param = std::make_tuple(12, "Hello World");
		Utils::replaceScene(GameWorld::create(), &param);
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
