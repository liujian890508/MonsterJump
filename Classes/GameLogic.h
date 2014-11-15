#ifndef __GAMEMAPLOGIC_H__
#define __GAMEMAPLOGIC_H__

#include "cocos2d.h"
#include "GameWorld.h"
#include "BaseSprite.h"
#include "TypeInfoDef.h"
USING_NS_CC;

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	bool initWithGameMap(GameWorld *gameWorld);

	static GameLogic* create(GameWorld *gameWorld);

	void update(float dt);
    
    void moveMapByHero();
	void checkContact();
	void loadMap();

private:
	GameWorld		*m_pGameWorld;
};

#endif