#ifndef __BASEENTITY_H__
#define __BASEENTITY_H__

#include "cocos2d.h"
USING_NS_CC;

enum EntityType
{
	kType_Hero,
	kType_Normal
};

template<typename T>
class BaseEntity: public Sprite
{
public:
	BaseEntity(){}
	virtual ~BaseEntity(){}

	virtual bool initEntity() = 0;
	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);

	EntityType getEntityType() const { return m_entityType; }
	void setEntityType(EntityType type){ this->m_entityType = type; }

	static T* create(const ValueMap &valueMap, const ValueMap &gidProperties);

protected:
	int				m_nGid;
	Vec2			_initVec;
	EntityType		m_entityType;
	std::string		m_sSource;
	std::string		m_sTypeName;
};

template<typename T>
T* BaseEntity<T>::create(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	auto t = new (std::nothrow) T();
	if (t && t->init(valueMap, gidProperties))
	{
		t->autorelease();
		return t;
	}
	CC_SAFE_RELEASE(t);
	return nullptr;
}

template<typename T>
bool BaseEntity<T>::init(const ValueMap &valueMap, const ValueMap &gidProperties)
{
	float x = valueMap.find("x")->second.asFloat();
	float y = valueMap.find("y")->second.asFloat();
	this->_initVec = Vec2(x, y);
	this->m_nGid = valueMap.find("gid")->second.asInt();
	this->m_sSource = gidProperties.find("source")->second.asString();
	this->m_sTypeName = gidProperties.find("type")->second.asString();
	if (!Sprite::initWithFile(m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(this->_initVec + this->getContentSize() / 2);
	return this->initEntity();
}

#endif