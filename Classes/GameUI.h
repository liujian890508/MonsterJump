#ifndef __GAMEUI_H__
#define __GAMEUI_H__

#include "BaseLayer.h"

class GameWorld;
class GameUI: public BaseLayer<GameUI>
{
public:
	GameUI();
	~GameUI();

	virtual bool init();

	void setGameWorld(GameWorld *gameWorld);

private:
	GameWorld		*m_pGameWorld;
};

#endif