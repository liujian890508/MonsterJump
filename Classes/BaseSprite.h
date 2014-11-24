#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include "cocos2d.h"
#include "TypeInfoDef.h"
#include "Box2D/Box2D.h"
USING_NS_CC;

class HeroSprite;
class BaseSprite : public Sprite
{
public:
	BaseSprite(){}
	virtual ~BaseSprite(){}

	EntityType getEntityType() const { return m_entityType; }
	void setEntityType(EntityType type){ this->m_entityType = type; }

	virtual void checkContact(HeroSprite *heroSprite){}

	virtual void BeginContact(b2Contact* contact, BaseSprite *sprite){ B2_NOT_USED(contact);}

	virtual void EndContact(b2Contact* contact, BaseSprite *sprite){ B2_NOT_USED(contact); }

protected:

	EntityType		m_entityType;
};

#endif