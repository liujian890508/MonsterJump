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
	this->setAnchorPoint(Vec2(0.5, 0));
	this->setPosition(_initVec + Point(this->getContentSize().width / 2, 0));
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
		auto seqAction = Sequence::create(
			ScaleTo::create(0.1f, 0.2f),
			CallFunc::create([=](){
				heroSprite->setPositionY(this->getPosition().y);
				heroSprite->setVelocity(heroSprite->getVelocity() + 200.0f);
			}),
			ScaleTo::create(0.1f, 1.0f),
			nullptr);
		this->runAction(seqAction);
	}
}
