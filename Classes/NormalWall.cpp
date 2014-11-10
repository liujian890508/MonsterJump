#include "NormalWall.h"
#include "HeroSprite.h"

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

void NormalWall::checkContact(HeroSprite *heroSprite)
{
	if (heroSprite->getMoveDir() == MoveDir_Down)
	{
		Point heroPos = heroSprite->getPosition();
		Size heroSize = heroSprite->getContentSize();
		Point wallPos = this->getPosition();
		Size wallSize = this->getContentSize();

		if (this->getBoundingBox().containsPoint(heroPos) ||
			this->getBoundingBox().containsPoint(heroPos + Point(30, 0)) ||
			this->getBoundingBox().containsPoint(heroPos - Point(30, 0)))
		{
			float y = wallPos.y + wallSize.height / 2 - 10;
			if (std::fabs(y - heroPos.y) > 5)
				heroSprite->setPositionY(y);
		}
	}
}
