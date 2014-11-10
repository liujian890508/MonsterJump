#include "Spring.h"


Spring::Spring()
{
}


Spring::~Spring()
{
}

bool Spring::initEntity()
{
	if (!BaseEntity::initWithFile(m_sSource)) return false;
	this->getTexture()->setAliasTexParameters();
	this->setPosition(_initVec + getContentSize() / 2);
	this->setEntityType(kType_Spring);
	return true;
}
