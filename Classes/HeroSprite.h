#ifndef __HEROSPRITE_H__
#define __HEROSPRITE_H__

#include "BaseEntity.h"
#include "TypeInfoDef.h"

#define VELOCITY 300
#define ACCELERATED -120

class HeroSprite: public BaseEntity<HeroSprite>
{
	friend class BaseEntity<HeroSprite>;
public:
	HeroSprite();
	~HeroSprite();

	void update(float dt);

	void onExit();

	void startJump();
	void gameOver();

	void setPositionY(float y);

	void setAccelerometerEnabled(bool enabled);

	void onAcceleration(Acceleration* acc, Event* unused_event);

	MoveDir getMoveDir() const{ return this->_moveUpOrDown; }

	void changeState(HeroState state);
	void changeDir(MoveDir dir);

	void setOffset(float offset);
protected:

	bool initEntity();

private:
	MoveDir			_moveUpOrDown;
	MoveDir			_moveLeftOrRight;
	Vec2			_previousPos;
	bool			_accelerometerEnabled;
	EventListenerAcceleration	*_accelerationListener;
	float			_offset;
	float			_time;
	float			_startPos;
};

#endif