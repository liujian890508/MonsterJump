#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include "cocos2d.h"
#include "TypeInfoDef.h"
USING_NS_CC;

class BaseSprite : public Sprite
{
public:
	BaseSprite(){}
	virtual ~BaseSprite(){}

	EntityType getEntityType() const { return m_entityType; }
	void setEntityType(EntityType type){ this->m_entityType = type; }

protected:

	EntityType		m_entityType;
};

#endif