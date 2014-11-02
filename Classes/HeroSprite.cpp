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
    if( unused_event->getType() == Event::Type::ACCELERATION)
    {
        float sensitivity = 25.0;
        float maxVelocity = 30.0f;
        
        CCLOG("%f", acc->x);
        
        _offset = acc->x*sensitivity;
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