#ifndef __BASEENTITY_H__
#define __BASEENTITY_H__

#include "BaseSprite.h"

template<typename T>
class BaseEntity: public BaseSprite
{
public:
	BaseEntity(){}
	virtual ~BaseEntity(){}

	static T* create(const ValueMap &valueMap, const ValueMap &gidProperties);

protected:

	bool initEntity(){ return true; }

	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);

protected:
	int				m_nGid;
	Vec2			_initVec;
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
	T *pt = static_cast<T*>(this);
	return pt->initEntity();
}

#endif