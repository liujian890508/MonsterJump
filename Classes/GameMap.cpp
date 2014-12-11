#include "GameMap.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "NormalWall.h"
#include "Collapsar.h"
#include "Plane.h"
#include "Bird.h"
#include "Gold.h"
#include "Spring.h"
#include "Utils.h"
#include "ObjectManager.h"

#include "2d/CCFastTMXTiledMap.h"
#include "2d/CCFastTMXLayer.h"

#define MAP_TAG 10

GameMap::GameMap()
{
	m_pGameWorld = nullptr;
}


GameMap::~GameMap()
{
}

bool GameMap::init()
{
	this->m_nCurrentHeight = 0;
	this->setContentSize(Size(640, 960));
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(0.5, 0.5));

	return true;
}

void GameMap::initWithMap()
{
	for (int i = 0; i < 1; i++)
	{
		this->loadMap(i + 1);
	}
}

void GameMap::loadMap(int mapId)
{
	this->m_nMapId = mapId;
	auto map = experimental::TMXTiledMap::create(String::createWithFormat("map/map_%d.tmx", mapId)->getCString());
	this->loadObject(map);
	m_nCurrentHeight += map->getMapSize().height * map->getTileSize().height;
}

void GameMap::loadObject(experimental::TMXTiledMap *map)
{
	TMXObjectGroup *objectGroup = map->getObjectGroup("game");
	if (objectGroup == nullptr) return;
	ValueVector objects = objectGroup->getObjects();
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		ValueMap objProperties = objects.at(i).asValueMap();
		ValueMap gidProperties = map->getPropertiesForGID(objProperties["gid"].asInt()).asValueMap();
		std::string type = gidProperties["type"].asString();
		BaseSprite *entity = nullptr;
		if (type == "brick")
			entity = NormalWall::create(objProperties, gidProperties);
		else if (type == "hero")
			this->m_pGameWorld->initHeroSprite(objProperties, gidProperties);
		else if (type == "collapsar")
			entity = Collapsar::create(objProperties, gidProperties);
		else if (type == "plane")
			entity = Plane::create(objProperties, gidProperties);
		else if (type == "bird")
			entity = Bird::create(objProperties, gidProperties);
		else if (type == "gold")
			entity = Gold::create(objProperties, gidProperties);
		else if (type == "spring")
			entity = Spring::create(objProperties, gidProperties);
		if (entity != nullptr)
		{
			this->addChild(entity);
			entity->setPosition(entity->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(entity);
		}
	}
}

void GameMap::update(float dt)
{
	
}

void GameMap::startGame()
{
	
}

void GameMap::gameOver()
{
	this->runAction(MoveBy::create(0.2f, Point(0, VisibleRect::top().y + 50)));
}

bool GameMap::databind(void *data)
{
	return true;
}

void GameMap::setGameWorld(GameWorld *gameWorld)
{
	m_pGameWorld = gameWorld;
}

void GameMap::move(Point point)
{
	this->setPosition(this->getPosition() - point);
}

void GameMap::loadMap()
{
	int curId = m_nMapId;
	if (curId >= MAXMAPID)
	{
		curId = Utils::getRandomInt(1, MAXMAPID);
	}
	else
	{
		curId++;
	}
	this->loadMap(curId);
}