#include "GameMapLogic.h"
#include "HeroSprite.h"
#include "GameWorld.h"
#include "VisibleRect.h"

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
	NormalVector* normals = this->m_pGameMap->getNormals();
	int count = 0;
	for (NormalVectorIt it = normals->begin(); it != normals->end();)
	{
		NormalWall *wall = *it;
		this->checkContact(wall);
		Point worldPos = wall->getParent()->convertToWorldSpace(wall->getPosition());
		if (worldPos.y < -wall->getContentSize().height / 2)
		{
			wall->removeFromParent();
			it = normals->erase(it);
		}
		else
			++it;
	}
    this->moveMapByHero();
}

void GameMapLogic::moveMapByHero()
{
 	HeroSprite *heroSprite = this->m_pGameMap->getGameWorld()->getHero();
    Vec2 worldPos = heroSprite->getParent()->convertToWorldSpace(heroSprite->getPosition());
    if( worldPos.y > VisibleRect::center().y)
    {
        float y = this->m_pGameMap->getPositionY() -
            worldPos.y + VisibleRect::center().y;
        this->m_pGameMap->setPositionY(y);
    }
}

void GameMapLogic::checkContact(NormalWall *wall)
{
	HeroSprite *heroSprite = this->m_pGameMap->getGameWorld()->getHero();
	Rect heroRect = heroSprite->getBoundingBox();
	Rect wallRect = wall->getBoundingBox();
	if (heroSprite->getMoveDir() == MoveDir_Down && heroRect.intersectsRect(wallRect) &&
        heroSprite->getPositionY() > wall->getPositionY() + wall->getContentSize().height / 2)
	{
		float y = wall->getPositionY() + wall->getContentSize().height / 2 +
			heroSprite->getContentSize().height / 2;
		if (std::fabs(y - heroSprite->getPositionY()) > 5)
			heroSprite->setPositionY(y);
	}
}
