#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "BaseLayer.h"

class GameMap;
class GameUI;
class GameWorld: public BaseLayer<GameWorld>
{
public:
	GameWorld();
	~GameWorld();

	bool init();
	bool initWithMap();
	bool initWithUI();

	bool databind(void *data);

	GameMap* getGameMap() const { return m_pGameMap; }
	GameUI* getGameUI() const{ return m_pGameUI; }

private:
	GameMap		*m_pGameMap;
	GameUI		*m_pGameUI;
};

#endif