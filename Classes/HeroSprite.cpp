#include "HeroSprite.h"
#include "VisibleRect.h"

HeroSprite::HeroSprite()
{
}


HeroSprite::~HeroSprite()
{
}

bool HeroSprite::initEntity()
{
	_offset = 0.0f;
	_moveDir = MoveDir_Up;
	return true;
}

void HeroSprite::setAccelerometerEnabled(bool enabled)
{
	if (enabled != _accelerometerEnabled)
	{
		_accelerometerEnabled = enabled;

		Device::setAccelerometerEnabled(enabled);

		_eventDispatcher->removeEventListener(_accelerationListener);
		_accelerationListener = nullptr;

		if (enabled)
		{
			_accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(HeroSprite::onAcceleration, this));
			_eventDispatcher->addEventListenerWithSceneGraphPriority(_accelerationListener, this);
		}
	}
}

void HeroSprite::onAcceleration(Acceleration* acc, Event* unused_event)
{
	float deceleration = 0.5f;
	//加速计的敏感值越大，主角对加速计的输入会越敏感   
	float sensitivity = 15.0;
	//最大移动距离   
	float maxVelocity = 30.0f;

	_offset = _offset*deceleration + acc->x*sensitivity;
	if (_offset >= maxVelocity)
	{
		_offset = maxVelocity;
	}
	else if (_offset <= -maxVelocity)
	{
		_offset = -maxVelocity;
	}
}

void HeroSprite::startJump()
{
	_previousPos = getPosition();
	auto seqAction = Sequence::create(
		JumpBy::create(1.2f, Vec2(0, 0), JUMP_HEIGHT, 1),
		nullptr);
	this->runAction(RepeatForever::create(seqAction));
	this->setAccelerometerEnabled(true);
	this->scheduleUpdate();
}

void HeroSprite::update(float dt)
{
	_moveDir = _previousPos.y > getPositionY() ? MoveDir_Down : MoveDir_Up;
	if (getPositionX() > VisibleRect::right().x + getContentSize().width / 2)
	{
		setPositionX(-getContentSize().width / 2);
	}
	else if (getPositionX() < -getContentSize().width / 2)
	{
		setPositionX(VisibleRect::right().x + getContentSize().width / 2);
	}
	setPositionX(getPositionX() + _offset);
}