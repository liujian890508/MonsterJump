#include "NormalWall.h"


NormalWall::NormalWall()
{
}


NormalWall::~NormalWall()
{
}

bool NormalWall::initEntity()
{
	if (!Sprite::initWithFile(m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(this->_initVec + this->getContentSize() / 2);
    setEntityType(EntityType::kType_Normal);
	return true;
}
