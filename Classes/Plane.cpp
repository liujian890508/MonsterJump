#include "Plane.h"


Plane::Plane()
{
}


Plane::~Plane()
{
}

bool Plane::initEntity()
{
	if (!BaseEntity::initWithFile(m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(_initVec + getContentSize() / 2);
	this->setEntityType(kType_Plane);
	return true;
}
