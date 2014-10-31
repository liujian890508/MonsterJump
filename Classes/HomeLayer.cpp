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
		Utils::replaceScene(GameWorld::create());
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
