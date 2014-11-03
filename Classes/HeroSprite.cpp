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
    setEntityType(EntityType::kType_Hero);
	_offset = 0.0f;
	_moveDir = MoveDir_None;
	return true;
}

void HeroSprite::setAccelerometerEnabled(bool enabled)
{
	if (enabled != _accelerometerEnabled)
	{
		_accelerometerEnabled = enabled;

		Device::setAccelerometerEnabled(enabled);
		Device::setAccelerometerInterval(0.01f);

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
    if( unused_event->getType() == Event::Type::ACCELERATION)
    {
        float sensitivity = 25.0;
        float maxVelocity = 30.0f;
        _offset = acc->x * sensitivity;
        if (_offset >= maxVelocity)
        {
            _offset = maxVelocity;
        }
        else if (_offset <= -maxVelocity)
        {
            _offset = -maxVelocity;
        }
    }
}

void HeroSprite::startJump()
{
	_previousPos = getPosition();
	this->setPositionY(getPositionY());
	this->setAccelerometerEnabled(true);
	this->scheduleUpdate();
}

void HeroSprite::onExit()
{
	BaseEntity::onExit();
	this->stopAllActions();
	this->setAccelerometerEnabled(false);
	this->unscheduleUpdate();
}

void HeroSprite::setPositionY(float y)
{
	this->_moveDir = MoveDir_None;
	this->stopAllActions();
	BaseEntity::setPositionY(y);
	auto seqAction = Sequence::create(
		JumpBy::create(1.2f, Vec2(0, -10), JUMP_HEIGHT, 1),
		MoveBy::create(1.5f, Point(0, -700)),
		nullptr);
	this->runAction(seqAction);
}

void HeroSprite::update(float dt)
{
	_moveDir = _previousPos.y > getPositionY() ? MoveDir_Down : MoveDir_Up;
	_previousPos = getPosition();
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