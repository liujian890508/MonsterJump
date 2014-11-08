#include "GameMapLogic.h"
#include "HeroSprite.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "ObjectManager.h"

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
	for (unsigned int i = 0; i < ObjectMgr->size(); i++)
	{
		auto baseSprite = ObjectMgr->get(i);
		switch (baseSprite->getEntityType())
		{
		case kType_Normal:
			this->checkContact(baseSprite);
			break;
		}
		Point worldPos = baseSprite->getParent()->convertToWorldSpace(baseSprite->getPosition());
		if (worldPos.y < -baseSprite->getContentSize().height / 2)
		{
			baseSprite->removeFromParent();
			ObjectMgr->remove(i);
		}
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
	if (worldPos.y <= 0)
	{
		m_pGameMap->getGameWorld()->gameOver();
	}
}

void GameMapLogic::checkContact(BaseSprite *wall)
{
	HeroSprite *heroSprite = this->m_pGameMap->getGameWorld()->getHero();
	if (heroSprite->getMoveDir() == MoveDir_Down)
	{
		Point heroPos = heroSprite->getPosition();
		Size heroSize = heroSprite->getContentSize();
		Point wallPos = wall->getPosition();
		Size wallSize = wall->getContentSize();

		if (wall->getBoundingBox().containsPoint(heroPos) || 
			wall->getBoundingBox().containsPoint(heroPos + Point(30, 0)) ||
			wall->getBoundingBox().containsPoint(heroPos - Point(30, 0)))
		{
			float y = wallPos.y + wallSize.height / 2 - 20;
			if (std::fabs(y - heroPos.y) > 5)
				heroSprite->setPositionY(y);
		}
	}
}
