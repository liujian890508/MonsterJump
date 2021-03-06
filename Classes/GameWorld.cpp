#include "GameWorld.h"
#include "GameMap.h"
#include "GameUI.h"
#include "HeroSprite.h"
#include "VisibleRect.h"
#include "GameLogic.h"
#include "Background.h"
#include "ObjectManager.h"

GameWorld::GameWorld()
{
	m_pGameLogic = nullptr;
}


GameWorld::~GameWorld()
{
	ObjectMgr->clear();
	delete this->m_pGameLogic;
}

bool GameWorld::init()
{
	this->setEntityType(kType_GameWorld);
	this->setMessageEnabled(true);

	m_pBgSprite = Background::create();
	this->addChild(m_pBgSprite);

	this->m_pGameLogic = GameLogic::create(this);
	addKeyboardSupport();
	this->initWithMap();
	this->initWithUI();
	return true;
}
 

void GameWorld::onEnterTransitionDidFinish()
{
    this->startGame();
}

bool GameWorld::initWithMap()
{
	this->m_pGameMap = GameMap::create();
	this->m_pGameMap->setGameWorld(this);
	this->m_pGameMap->initWithMap();
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
    int id;
    std::string desc;
    std::tie(id, desc) = *static_cast<std::tuple<int, std::string>*>(data);
	return true;
}

bool GameWorld::initHeroSprite(ValueMap &objProperties, ValueMap& gidProperties)
{
	this->m_pHeroSprite = HeroSprite::create(objProperties,gidProperties);
	this->m_pGameMap->addChild(m_pHeroSprite, 10);
	ObjectMgr->put(m_pHeroSprite);
	return true;
}

void GameWorld::startGame()
{
	this->m_pGameLogic->startGame();
	this->m_pGameMap->startGame();
	this->m_pHeroSprite->startJump();
	this->scheduleUpdate();
}

void GameWorld::gameOver()
{
	this->m_pGameLogic->gameOver();
	this->m_pHeroSprite->gameOver();
	this->m_pGameMap->gameOver();
}

void GameWorld::move(Point point)
{
	this->m_pGameMap->move(point);
	this->m_pBgSprite->move(point);
}

void GameWorld::update(float dt)
{
	this->m_pHeroSprite->update(dt);
	this->m_pGameMap->update(dt);
	this->m_pGameLogic->update(dt);
}

void GameWorld::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A ) 
	{
		this->m_pHeroSprite->setOffset(-4);
		this->m_pHeroSprite->changeDir(MoveDir_Right);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D ) 
	{
		this->m_pHeroSprite->setOffset(4);
		this->m_pHeroSprite->changeDir(MoveDir_Left);
	}
}

void GameWorld::onKeyReleased( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
	//release 
	this->m_pHeroSprite->setOffset(0);
}
