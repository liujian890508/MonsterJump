#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "BaseLayer.h"

class GameWorld;
class GameMap: public BaseLayer<GameMap>
{
public:
	GameMap();
	virtual ~GameMap();

	virtual bool init();
	virtual bool databind(void *data);

	void setGameWorld(GameWorld *gameWorld);

private:
	GameWorld		*m_pGameWorld;
};

#endif