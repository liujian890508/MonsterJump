#include "BrokenWall.h"
#include "HeroSprite.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "..\cocos2d\cocos\editor-support\cocostudio\ActionTimeline\CCActionTimeline.h"
#include "ObjectManager.h"
using namespace cocostudio;
BrokenWall::BrokenWall()
{
}


BrokenWall::~BrokenWall()
{
}

bool BrokenWall::initEntity()
{
	if (!Sprite::initWithFile(m_sSource)) return false;
	getTexture()->setAliasTexParameters();
	this->setPosition(this->_initVec + this->getContentSize() / 2);
    setEntityType(EntityType::kType_Normal);
	return true;
}

void BrokenWall::checkContact(HeroSprite *heroSprite)
{
	if (heroSprite->getMoveDir() == MoveDir_Down)
	{
		Point heroPos = heroSprite->getPosition();
		Size heroSize = heroSprite->getContentSize();
		Point wallPos = this->getPosition();
		Size wallSize = this->getContentSize();

		if (std::abs(heroPos.y - (wallPos.y + wallSize.height / 2)) < 15)
		{
			if (heroPos.x > wallPos.x - wallSize.width / 2 && heroPos.x < wallPos.x + wallSize.width / 2)
			{
				float y = wallPos.y + wallSize.height / 2 - 5;
				if (std::fabs(y - heroPos.y) > 5)
					heroSprite->setPositionY(y);

				//playanimation("effect/brick_break.csb")
				Node * brickeffect = CSLoader::createNode("effect/brick_break.csb");
				timeline::ActionTimeline * action  = CSLoader::createTimeline("effect/brick_break.csb");
				action->gotoFrameAndPlay(0, false);  
				//brickeffect->setPosition(getContentSize()/2);
				brickeffect->runAction(action);
				addChild(brickeffect);
				ObjectMgr->remove(this);
				setTexture(nullptr);
				setTextureRect(Rect::ZERO);
				action->setLastFrameCallFunc([=](){
					this->removeFromParentAndCleanup(true);
				});

				//this->deleteLater();
				//this->setVisible(false);

			}
		}

	}
}
