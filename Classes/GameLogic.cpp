#include "GameLogic.h"
#include "HeroSprite.h"
#include "GameWorld.h"
#include "VisibleRect.h"
#include "ObjectManager.h"

GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}

GameLogic* GameLogic::create(GameWorld *gameWorld)
{
	auto mapLogic = new (std::nothrow) GameLogic();
	if (mapLogic && mapLogic->initWithGameMap(gameWorld))
	{
		return mapLogic;
	}
	return nullptr;
}

bool GameLogic::initWithGameMap(GameWorld *gameWorld)
{
	this->m_pGameWorld = gameWorld;
	return true;
}

void GameLogic::update(float dt)
{
	HeroSprite *heroSprite = this->m_pGameWorld->getHero();
	for (unsigned int i = 0; i < ObjectMgr->size(); i++)
	{
		auto baseSprite = ObjectMgr->get(i);
		baseSprite->checkContact(heroSprite);
		Point worldPos = baseSprite->getParent()->convertToWorldSpace(baseSprite->getPosition());
		if (worldPos.y < -baseSprite->getContentSize().height / 2)
		{
			baseSprite->removeFromParent();
			ObjectMgr->remove(i);
		}
	}
    this->moveMapByHero();
}

void GameLogic::moveMapByHero()
{
 	HeroSprite *heroSprite = this->m_pGameWorld->getHero();
    Vec2 worldPos = heroSprite->getParent()->convertToWorldSpace(heroSprite->getPosition());
    if( worldPos.y > VisibleRect::center().y)
    {
		this->m_pGameWorld->move(Point(0, worldPos.y - VisibleRect::center().y));
    }
	if (worldPos.y <= 0)
	{
		m_pGameWorld->gameOver();
	}
}
