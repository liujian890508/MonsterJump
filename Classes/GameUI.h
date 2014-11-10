#ifndef __GAMEUI_H__
#define __GAMEUI_H__

#include "BaseLayer.h"

class Background;
class GameWorld;
class GameUI: public BaseLayer<GameUI>
{
public:
	GameUI();
	~GameUI();

	virtual bool init();

	void move(Point point);

	void setGameWorld(GameWorld *gameWorld);

private:
	GameWorld		*m_pGameWorld;
	Background		*m_pBgSprite;
};

#endif