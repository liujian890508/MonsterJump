#ifndef __GAMEWORLD_H__
#define __GAMEWORLD_H__

#include "BaseLayer.h"

class GameMap;
class GameUI;
class HeroSprite;
class GameLogic;
class GameWorld: public BaseLayer<GameWorld>
{
public:
	GameWorld();
	~GameWorld();

	bool init();
	bool initWithMap();
	bool initWithUI();
	bool initHeroSprite(ValueMap &objProperties, ValueMap& gidProperties);
    
    virtual void onEnterTransitionDidFinish();

	bool databind(void *data);

	void startGame();
	void gameOver();

	void update(float dt);

	void move(Point point);

	GameMap* getGameMap() const { return m_pGameMap; }
	GameUI* getGameUI() const{ return m_pGameUI; }
    HeroSprite* getHero() const { return m_pHeroSprite; }

private:
	GameMap		*m_pGameMap;
	GameUI		*m_pGameUI;
	HeroSprite  *m_pHeroSprite;
	GameLogic	*m_pGameLogic;
};

#endif