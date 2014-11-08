#include "Bird.h"


Bird::Bird()
{
}


Bird::~Bird()
{
}

bool Bird::initEntity()
{
	if (!BaseEntity::initWithFile(m_sSource)) return false;
	this->getTexture()->setAliasTexParameters();
	this->setPosition(_initVec + getContentSize() / 2);
	return true;
}
