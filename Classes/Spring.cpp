#include "Spring.h"
#include "HeroSprite.h"

Spring::Spring()
{
	m_bIsContact = false;
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

void Spring::checkContact(HeroSprite *heroSprite)
{
	if (m_bIsContact) return;
	Point heroPoint = heroSprite->getPosition();
	if ((this->getPosition() - heroPoint).length() < this->getContentSize().height / 2)
	{
		m_bIsContact = true;
		this->setScaleY(0.5);
		heroSprite->setPositionY(this->getPosition().y);
		heroSprite->setVelocity(heroSprite->getVelocity() + 200.0f);
	}
}
