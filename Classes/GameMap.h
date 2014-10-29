#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "BaseLayer.h"

class GameMap: public BaseLayer<GameMap>
{
public:
	GameMap();
	virtual ~GameMap();

	virtual bool init();
	virtual bool databind(void *data);
};

#endif