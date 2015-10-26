#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "BaseLayer.h"
#include "TypeInfoDef.h"

#define MAXMAPID 1

class GameWorld;
class GameMap: public BaseLayer<GameMap>
{
public:
	GameMap();
	virtual ~GameMap();

	virtual bool init();
	void initWithMap();
	void loadObject(experimental::TMXTiledMap *map);
	virtual bool databind(void *data);

	void startGame();
	void gameOver();

	void update(float dt);
	void loadMap();
	void loadMap(int mapId);
	void move(Point point);

	void setGameWorld(GameWorld *gameWorld);
	GameWorld* getGameWorld() const { return m_pGameWorld; }

private:
	GameWorld		*m_pGameWorld;
	int				m_nCurrentHeight;
	int				m_nMapId;
};

#endif