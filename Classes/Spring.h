#ifndef __SPRING_H__
#define __SPRING_H__

#include "BaseEntity.h"

class Spring: public BaseEntity<Spring>
{
	friend class BaseEntity<Spring>;
public:
	Spring();
	~Spring();

	virtual void checkContact(HeroSprite *heroSprite);

protected:
	bool initEntity();

private:
	bool m_bIsContact;
};

#endif