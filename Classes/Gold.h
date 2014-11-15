#ifndef __GOLD_H__
#define __GOLD_H__

#include "BaseEntity.h"

class Gold: public BaseEntity<Gold>
{
	friend class BaseEntity<Gold>;
public:
	Gold();
	~Gold();

	virtual void checkContact(HeroSprite *heroSprite);

	void playMoveAni();

protected:
	
	bool initEntity();

private:
	bool		m_bIsContact;
};

#endif