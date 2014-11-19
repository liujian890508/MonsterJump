#ifndef __BIRD_H__
#define __BIRD_H__

#include "BaseEntity.h"

class Bird: public BaseEntity<Bird>
{
	friend class BaseEntity<Bird>;
public:
	Bird();
	~Bird();

protected:

	bool initEntity();

	void flyAnimate();
};

#endif