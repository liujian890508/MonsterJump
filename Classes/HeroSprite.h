#ifndef __HEROSPRITE_H__
#define __HEROSPRITE_H__

#include "BaseEntity.h"

#define JUMP_HEIGHT 300

enum MoveDir
{
	MoveDir_Up,
	MoveDir_Down
};
class HeroSprite: public BaseEntity<HeroSprite>
{
public:
	HeroSprite();
	~HeroSprite();

	void update(float dt);

	bool initEntity();

	void startJump();

	void setAccelerometerEnabled(bool enabled);

	virtual void onAcceleration(Acceleration* acc, Event* unused_event);

private:
	MoveDir			_moveDir;
	Vec2			_previousPos;
	bool			_accelerometerEnabled;
	EventListenerAcceleration	*_accelerationListener;
	float			_offset;
};

#endif