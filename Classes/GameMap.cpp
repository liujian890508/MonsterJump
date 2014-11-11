#include "GameMap.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "NormalWall.h"
#include "Collapsar.h"
#include "Plane.h"
#include "Bird.h"
#include "Gold.h"
#include "Spring.h"
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
	this->setContentSize(Size(640, 960));
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(0.5, 0.5));

	return true;
}

void GameMap::initWithMap()
{
	float height = 0.0f;
	for (int i = 0; i < 10; i++)
	{
		auto map = experimental::TMXTiledMap::create(String::createWithFormat("map/map_%d.tmx", i + 1)->getCString());
		this->addChild(map, 0, MAP_TAG + i);
		map->setPosition(VisibleRect::leftBottom() + Point(0, height));
		this->loadObject(map, height);
		height += map->getMapSize().height * map->getTileSize().height;
	}
}

void GameMap::loadObject(experimental::TMXTiledMap *map, int height)
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
            normalWall->setPosition(normalWall->getPosition() + Point(0, height));
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
			collapsar->setPosition(collapsar->getPosition() + Point(0, height));
			ObjectMgr->put(collapsar);
		}
		else if (type == "plane")
		{
			auto plane = Plane::create(objProperties, gidProperties);
			this->addChild(plane);
			plane->setPosition(plane->getPosition() + Point(0, height));
			ObjectMgr->put(plane);
		}
		else if (type == "bird")
		{
			auto bird = Bird::create(objProperties, gidProperties);
			this->addChild(bird);
			bird->setPosition(bird->getPosition() + Point(0, height));
			ObjectMgr->put(bird);
		}
		else if (type == "gold")
		{
			auto gold = Gold::create(objProperties, gidProperties);
			this->addChild(gold);
			gold->setPosition(gold->getPosition() + Point(0, height));
			ObjectMgr->put(gold);
		}
		else if (type == "spring")
		{
			auto spring = Spring::create(objProperties, gidProperties);
			this->addChild(spring);
			spring->setPosition(spring->getPosition() + Point(0, height));
			ObjectMgr->put(spring);
		}
	}
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