#include "GameMap.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "GameMapLogic.h"

#include "2d/CCFastTMXTiledMap.h"
#include "2d/CCFastTMXLayer.h"

#define MAP_TAG 10

GameMap::GameMap()
{
	m_pGameWorld = nullptr;
	m_pGameMapLogic = nullptr;
}


GameMap::~GameMap()
{
	CC_SAFE_RELEASE(this->m_pGameWorld);
	delete m_pGameMapLogic;
}

bool GameMap::init()
{
	m_pGameMapLogic = GameMapLogic::create(this);
	this->setContentSize(Size(640, 960));
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(0.5, 0.5));

	this->_map = experimental::TMXTiledMap::create("map/map_1.tmx");
	this->addChild(this->_map, MAP_TAG);
	this->_map->setPosition(VisibleRect::leftBottom());

	return true;
}

void GameMap::loadAllObject()
{
	m_allNormals.clear();
	TMXObjectGroup *objectGroup = this->_map->getObjectGroup("game");
	if (objectGroup == nullptr) return;
	ValueVector objects = objectGroup->getObjects();
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		ValueMap objProperties = objects.at(i).asValueMap();
		ValueMap gidProperties = this->_map->getPropertiesForGID(objProperties["gid"].asInt()).asValueMap();
		std::string type = gidProperties["type"].asString();
		if (type == "brick")
		{
			auto normalWall = NormalWall::create(objProperties, gidProperties);
			this->addChild(normalWall);
			this->m_allNormals.push_back(normalWall);
		}
		else if (type == "hero")
		{
			this->m_pGameWorld->initHeroSprite(objProperties, gidProperties);
		}
	}
	this->scheduleUpdate();
}

void GameMap::update(float dt)
{
	m_pGameMapLogic->update(dt);
}

bool GameMap::databind(void *data)
{
	return true;
}

void GameMap::setGameWorld(GameWorld *gameWorld)
{
	CC_SAFE_RELEASE(m_pGameWorld);
	m_pGameWorld = gameWorld;
	CC_SAFE_RETAIN(m_pGameWorld);
	
}