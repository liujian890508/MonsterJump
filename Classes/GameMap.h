#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "BaseLayer.h"
#include "TypeInfoDef.h"

class GameWorld;
class GameMap: public BaseLayer<GameMap>
{
public:
	GameMap();
	virtual ~GameMap();

	virtual bool init();
	void initWithMap();
	void loadObject(experimental::TMXTiledMap *map, int height);
	virtual bool databind(void *data);

	void startGame();
	void gameOver();

	void move(Point point);

	void setGameWorld(GameWorld *gameWorld);
	GameWorld* getGameWorld() const { return m_pGameWorld; }

private:
	GameWorld		*m_pGameWorld;
};

#endif