#include "Bird.h"
#include "Utils.h"
#include "VisibleRect.h"

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
	this->setEntityType(kType_Bird);

	this->flyAnimate();
	return true;
}

void Bird::flyAnimate()
{
	auto animate = Utils::getAnimate("bird_", 1, 13, 0.05f);
	this->runAction(RepeatForever::create( animate));
	Point currentPos = this->getPosition() - Point(100, 0);
	Point targetPos = Point(VisibleRect::right().x + 50, currentPos.y);
	auto seqAction = Sequence::create(
		MoveTo::create(5.0f, targetPos),
		Place::create(currentPos),
		nullptr);
	this->runAction(RepeatForever::create(seqAction));
}
