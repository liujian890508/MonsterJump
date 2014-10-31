#include "GameWorld.h"
#include "GameMap.h"
#include "GameUI.h"
#include "HeroSprite.h"
#include "VisibleRect.h"

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

bool GameWorld::init()
{
	if (!LayerColor::initWithColor(Color4B(125, 0, 0, 255))) return false;
	this->initWithUI();
	this->initWithMap();
	this->startGame();
	return true;
}

bool GameWorld::initWithMap()
{
	this->m_pGameMap = GameMap::create();
	this->m_pGameMap->setGameWorld(this);
	this->m_pGameMap->loadAllObject();
	this->addChild(this->m_pGameMap);
	m_pGameMap->setPosition(VisibleRect::center());
	return true;
}

bool GameWorld::initWithUI()
{
	this->m_pGameUI = GameUI::create();
	this->m_pGameUI->setGameWorld(this);
	this->addChild(this->m_pGameUI);
	return true;
}

bool GameWorld::databind(void *data)
{
	return true;
}

bool GameWorld::initHeroSprite(ValueMap &objProperties, ValueMap& gidProperties)
{
	this->m_pHeroSprite = HeroSprite::create(objProperties,gidProperties);
	this->m_pGameMap->addChild(m_pHeroSprite);
	return true;
}

void GameWorld::startGame()
{
	this->m_pHeroSprite->startJump();
}
