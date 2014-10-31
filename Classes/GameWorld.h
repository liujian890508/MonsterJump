#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "BaseLayer.h"

class GameMap;
class GameUI;
class HeroSprite;
class GameWorld: public BaseLayer<GameWorld>
{
public:
	GameWorld();
	~GameWorld();

	bool init();
	bool initWithMap();
	bool initWithUI();
	bool initHeroSprite(ValueMap &objProperties, ValueMap& gidProperties);

	bool databind(void *data);

	void startGame();

	GameMap* getGameMap() const { return m_pGameMap; }
	GameUI* getGameUI() const{ return m_pGameUI; }

private:
	GameMap		*m_pGameMap;
	GameUI		*m_pGameUI;
	HeroSprite  *m_pHeroSprite;
};

#endif