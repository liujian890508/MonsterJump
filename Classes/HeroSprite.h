#ifndef __HEROSPRITE_H__
#define __HEROSPRITE_H__

#include "BaseEntity.h"
#include "TypeInfoDef.h"

#define JUMP_HEIGHT 200

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

	virtual void onAcceleration(Acceleration* acc, Event* unused_event);

	MoveDir getMoveDir() const{ return this->_moveDir; }

protected:

	bool initEntity();

private:
	MoveDir			_moveDir;
	Vec2			_previousPos;
	bool			_accelerometerEnabled;
	EventListenerAcceleration	*_accelerationListener;
	float			_offset;
};

#endif