#ifndef __HEROSPRITE_H__
#define __HEROSPRITE_H__

#include "BaseEntity.h"
#include "TypeInfoDef.h"

#define VELOCITY 200
#define ACCELERATED -98

class HeroSprite: public BaseEntity<HeroSprite>
{
	friend class BaseEntity<HeroSprite>;
public:
	HeroSprite();
	~HeroSprite();

	void update(float dt);

	void onExit();

	void startJump();

	void setPositionY(float y);

	void setAccelerometerEnabled(bool enabled);

	void onAcceleration(Acceleration* acc, Event* unused_event);

	MoveDir getMoveDir() const{ return this->_moveDir; }

	void changeState(HeroState state);

protected:

	bool initEntity();

private:
	MoveDir			_moveDir;
	Vec2			_previousPos;
	bool			_accelerometerEnabled;
	EventListenerAcceleration	*_accelerationListener;
	float			_offset;
	float			_time;
	float			_startPos;
};

#endif