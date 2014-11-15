#include "GameUI.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "Utils.h"
#include "HomeLayer.h"
#include "Background.h"

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
	auto pauseMenu = MenuItemImage::create("ui/buttons.png", "ui/buttons.png", [=](Ref *pSender){
		Utils::replaceScene(HomeLayer::create());
	});
	auto menu = Menu::create(pauseMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(VisibleRect::rightTop() - pauseMenu->getContentSize() / 2 - Point(5, 5));

	auto goldSprite = Sprite::create("map/item/item_coin.png");
	auto size = goldSprite->getContentSize() / 2;
	auto point = VisibleRect::leftTop();
	goldSprite->setPosition(Point(point.x + size.width + 5, point.y - size.height - 5));
	this->addChild(goldSprite);
	return true;
}
