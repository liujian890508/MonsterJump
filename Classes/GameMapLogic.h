#ifndef __GAMEMAPLOGIC_H__
#define __GAMEMAPLOGIC_H__

#include "cocos2d.h"
#include "GameMap.h"
#include "TypeInfoDef.h"
USING_NS_CC;

class GameMapLogic
{
public:
	GameMapLogic();
	~GameMapLogic();

	bool initWithGameMap(GameMap *gameMap);

	static GameMapLogic* create(GameMap *gameMap);

	void update(float dt);

	void checkContact(NormalWall* wall);
    
    void moveMapByHero();

private:
	GameMap		*m_pGameMap;
};

#endif