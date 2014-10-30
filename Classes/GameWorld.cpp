#include "GameWorld.h"
#include "GameMap.h"
#include "GameUI.h"

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

bool GameWorld::init()
{
	CCLOG("welcome to GameWorld");
	this->initWithMap();
	this->initWithUI();
	return true;
}

bool GameWorld::initWithMap()
{
	this->m_pGameMap = GameMap::create();
	this->m_pGameMap->setGameWorld(this);
	this->addChild(this->m_pGameMap);
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
	int num;
	std::string param;
	std::tie(num, param) = *static_cast<std::tuple<int, std::string>*>(data);
	CCLOG("%d -- %s",num, param.c_str());
	return true;
}
