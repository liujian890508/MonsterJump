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
	CC_SAFE_RELEASE(this->m_pGameWorld);
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
	for (int i = 0; i < 3; i++)
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
		if (type == "brick")
		{
			auto normalWall = NormalWall::create(objProperties, gidProperties);
			this->addChild(normalWall);
			normalWall->setPosition(normalWall->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(normalWall);
		}
		else if (type == "hero")
		{
			this->m_pGameWorld->initHeroSprite(objProperties, gidProperties);
		}
		else if (type == "collapsar")
		{
			auto collapsar = Collapsar::create(objProperties, gidProperties);
			this->addChild(collapsar);
			collapsar->setPosition(collapsar->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(collapsar);
		}
		else if (type == "plane")
		{
			auto plane = Plane::create(objProperties, gidProperties);
			this->addChild(plane);
			plane->setPosition(plane->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(plane);
		}
		else if (type == "bird")
		{
			auto bird = Bird::create(objProperties, gidProperties);
			this->addChild(bird);
			bird->setPosition(bird->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(bird);
		}
		else if (type == "gold")
		{
			auto gold = Gold::create(objProperties, gidProperties);
			this->addChild(gold);
			gold->setPosition(gold->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(gold);
		}
		else if (type == "spring")
		{
			auto spring = Spring::create(objProperties, gidProperties);
			this->addChild(spring);
			spring->setPosition(spring->getPosition() + Point(0, m_nCurrentHeight));
			ObjectMgr->put(spring);
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
	this->runAction(MoveBy::create(0.2f, Point(0, VisibleRect::top().y)));
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