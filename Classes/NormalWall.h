#ifndef __NORMALWALL_H__
#define __NORMALWALL_H__

#include "BaseEntity.h"

class HeroSprite;
class NormalWall: public BaseEntity<NormalWall>
{
	friend class BaseEntity<NormalWall>;
public:
	NormalWall();
	~NormalWall();

	virtual void checkContact(HeroSprite *heroSprite);

protected:

	bool initEntity();

};

#endif