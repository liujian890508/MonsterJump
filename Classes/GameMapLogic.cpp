#include "GameMapLogic.h"
#include "HeroSprite.h"
#include "GameWorld.h"

GameMapLogic::GameMapLogic()
{
}


GameMapLogic::~GameMapLogic()
{
}

GameMapLogic* GameMapLogic::create(GameMap *gameMap)
{
	auto mapLogic = new (std::nothrow) GameMapLogic();
	if (mapLogic && mapLogic->initWithGameMap(gameMap))
	{
		return mapLogic;
	}
	return nullptr;
}

bool GameMapLogic::initWithGameMap(GameMap *gameMap)
{
	this->m_pGameMap = gameMap;
	return true;
}

void GameMapLogic::update(float dt)
{
	NormalVector normals = this->m_pGameMap->getNormals();
	for (NormalVectorIt it = normals.begin(); it != normals.end(); it++)
	{
		NormalWall *wall = *it;
		this->checkContact(wall);
		Point worldPos = wall->getParent()->convertToWorldSpace(wall->getPosition());
		if (worldPos.y < -wall->getContentSize().height / 2)
		{
			wall->removeFromParent();
		}
	}
}

void GameMapLogic::checkContact(NormalWall *wall)
{
	HeroSprite *heroSprite = this->m_pGameMap->getGameWorld()->getHero();
	Rect heroRect = heroSprite->getBoundingBox();
	Rect wallRect = wall->getBoundingBox();
	if (heroSprite->getMoveDir() == MoveDir_Down && heroRect.intersectsRect(wallRect))
	{
		float y = wall->getPositionY() + wall->getContentSize().height / 2 +
			heroSprite->getContentSize().height / 2;
		if (std::fabs(y - heroSprite->getPositionY()) > 5)
			heroSprite->setPositionY(y);
	}
}
