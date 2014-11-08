#include "Collapsar.h"


Collapsar::Collapsar()
{
}


Collapsar::~Collapsar()
{
}

bool Collapsar::initEntity()
{
	if (!BaseSprite::initWithFile(this->m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(this->_initVec + this->getContentSize() / 2);
	this->setEntityType(kType_Collapsar);

	ParticleSystem *particleSystem = ParticleSystemQuad::create("effect/blackhole.plist");
	this->addChild(particleSystem);
	return true;
}
