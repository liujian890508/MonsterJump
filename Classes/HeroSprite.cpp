#include "HeroSprite.h"
#include "VisibleRect.h"
#include "Utils.h"

HeroSprite::HeroSprite()
{
	this->_accelerated = DEFAULT_ACCELERATED;
	this->_velocity = DEFAULT_VELOCITY;
	this->_isStartGame = false;
	this->_isGameOver = false;
}


HeroSprite::~HeroSprite()
{
}

bool HeroSprite::initEntity()
{
	if (!Sprite::initWithFile(m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(this->_initVec + Point(this->getContentSize().width / 2, 0));
    setEntityType(EntityType::kType_Hero);
    this->setAnchorPoint(Point(0.5, 0));
	_offset = 0.0f;
	_moveUpOrDown = MoveDir_None;
	_moveLeftOrRight = MoveDir_None;
	return true;
}

void HeroSprite::setAccelerometerEnabled(bool enabled)
{
	if (enabled != _accelerometerEnabled)
	{
		_accelerometerEnabled = enabled;

		Device::setAccelerometerEnabled(enabled);
		Device::setAccelerometerInterval(0.1f);

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
    if( unused_event->getType() == Event::Type::ACCELERATION && std::abs(acc->x) > 0.03)
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
		if (_offset > 0.6f) this->changeDir(MoveDir_Left);
		else if (_offset < -0.6f) this->changeDir(MoveDir_Right);
    }
}

void HeroSprite::startJump()
{
	_previousPos = getPosition();
	this->setPositionY(getPositionY());
	this->setAccelerometerEnabled(true);
	this->_isStartGame = true;
}

void HeroSprite::gameOver()
{
	this->_isGameOver = true;
}

void HeroSprite::onExit()
{
	BaseEntity::onExit();
	this->setAccelerometerEnabled(false);
	this->stopAllActions();
	this->gameOver();
	this->_isStartGame = false;
}

void HeroSprite::setPositionY(float y)
{
	this->_moveUpOrDown = MoveDir_None;
	this->_time = 0.0f;
	BaseEntity::setPositionY(y);
	_previousPos = Point(_previousPos.x, y);
	this->_startPos = y;
	this->changeState(kState_jump);
	this->_velocity = DEFAULT_VELOCITY;
}

void HeroSprite::update(float dt)
{
	if (!_isStartGame) return;
	Point wroldPos = this->getParent()->convertToWorldSpace(getPosition());
	if (_isGameOver && wroldPos.y < -getContentSize().height)
	{
		_isStartGame = false;
	}
	_time += dt * 2.5f;
	//215 = 49 * t
	float s = this->_velocity * _time + _accelerated * _time * _time / 2;
	MoveDir dir = _previousPos.y > getPositionY() ? MoveDir_Down : MoveDir_Up;
	this->changeDir(dir);
	_previousPos = getPosition();
	if (getPositionX() > VisibleRect::right().x + getContentSize().width / 2)
	{
		setPositionX(-getContentSize().width / 2);
	}
	else if (getPositionX() < -getContentSize().width / 2)
	{
		setPositionX(VisibleRect::right().x + getContentSize().width / 2);
	}
	setPosition(Point(getPositionX() + _offset, this->_startPos + s));
}

void HeroSprite::changeState(HeroState state)
{
	this->stopAllActions();
	Animate* animate = nullptr;
	switch (state)
	{
	case kState_fall:
		animate = Utils::getAnimate("rabbit_", 7, 12, 0.05f);
		break;
	case kState_jump:
		animate = Utils::getAnimate("rabbit_", 1, 6, 0.08f);
		break;
	case kState_rush:
		animate = Utils::getAnimate("rabbit_", 13, 18);
		break;
	case kState_rush_end:
		animate = Utils::getAnimate("rabbit_", 19, 24);
		break;
	case kState_walk:
		animate = Utils::getAnimate("rabbit_", 25, 35);
		break;
	}
	this->runAction(animate);
}

void HeroSprite::changeDir(MoveDir dir)
{
	if ((dir == MoveDir_Left || dir == MoveDir_Right) && _moveLeftOrRight != dir)
	{
		_moveLeftOrRight = dir;
		this->setFlippedX(_moveLeftOrRight == MoveDir_Right);
	}
	else if ((dir == MoveDir_Down || dir == MoveDir_Up) && _moveUpOrDown != dir)
	{
		_moveUpOrDown = dir;
        if( _moveUpOrDown == MoveDir_Down)
        {
            this->stopAllActions();
            this->changeState(kState_fall);
        }
	}
}

void HeroSprite::setOffset( float offset )
{
	_offset = offset;
}
