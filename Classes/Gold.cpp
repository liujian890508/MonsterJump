#include "Gold.h"
#include "HeroSprite.h"
#include "VisibleRect.h"
#include "ObjectManager.h"

Gold::Gold()
{
	m_bIsContact = false;
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

void Gold::checkContact(HeroSprite *heroSprite)
{
	if (m_bIsContact)return;
	Point heroPoint = heroSprite->getPosition();
	if ((heroPoint - this->getPosition()).length() < this->getContentSize().height / 2)
	{
		m_bIsContact = true;
		this->playMoveAni();
		//play get animation
		//this->removeFromParentAndCleanup(true);
		//ObjectMgr->remove(this);
			
	}
}

void Gold::playMoveAni()
{
	//Point movePoint = this->convertToNodeSpace(VisibleRect::leftTop());
	auto seqAction = Sequence::create(
		FadeOut::create(0.5f),
		CallFuncN::create([=](Node *pSender){
			this->removeFromParent();
			ObjectMgr->remove(this);
		}),
		nullptr);
	this->runAction(seqAction);
}

