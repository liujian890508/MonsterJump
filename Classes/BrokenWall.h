#ifndef __BrokenWall_H__
#define __BrokenWall_H__

#include "BaseEntity.h"

class HeroSprite;
class BrokenWall: public BaseEntity<BrokenWall>
{
	friend class BaseEntity<BrokenWall>;
public:
	BrokenWall();
	~BrokenWall();

	virtual void checkContact(HeroSprite *heroSprite);

protected:

	bool initEntity();

};

#endif