#include "GameUI.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "HomeLayer.h"

GameUI::GameUI()
{
	this->m_pGameWorld = nullptr;
}

GameUI::~GameUI()
{
	CC_SAFE_RELEASE(m_pGameWorld);
}

void GameUI::setGameWorld(GameWorld *gameWorld)
{
	CC_SAFE_RELEASE(m_pGameWorld);
	m_pGameWorld = gameWorld;
	CC_SAFE_RETAIN(m_pGameWorld);
}

bool GameUI::init()
{
	auto closeMenu = MenuItemFont::create("Close", [=](Ref *pSender){
		Utils::replaceScene(HomeLayer::create());
	});
	auto menu = Menu::create(closeMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::rightTop() - closeMenu->getContentSize() / 2);
	return true;
}