#include "Gold.h"


Gold::Gold()
{
}


Gold::~Gold()
{
}

bool Gold::initEntity()
{
	if (!BaseEntity::initWithFile(m_sSource)) return false;
	this->getTexture()->setAliasTexParameters();
	this->setPosition(_initVec + getContentSize() / 2);
	this->setEntityType(kType_Gold);
	return true;
}
