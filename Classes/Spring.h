#ifndef __SPRING_H__
#define __SPRING_H__

#include "BaseEntity.h"

class Spring: public BaseEntity<Spring>
{
	friend class BaseEntity<Spring>;
public:
	Spring();
	~Spring();

protected:
	bool initEntity();
};

#endif