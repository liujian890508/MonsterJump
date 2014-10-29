#include "GameUI.h"
#include "GameWorld.h"

GameUI::GameUI()
{
	this->m_pGameWorld = nullptr;
}

GameUI::~GameUI()
{
	CC_SAFE_RELEASE(m_pGameWorld);
}

void GameUI::setGameWorld(GameWorld *gameWorld)
{
	CC_SAFE_RELEASE(m_pGameWorld);
	m_pGameWorld = gameWorld;
	CC_SAFE_RETAIN(m_pGameWorld);
}