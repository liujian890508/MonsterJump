#ifndef __GOLD_H__
#define __GOLD_H__

#include "BaseEntity.h"

class Gold: public BaseEntity<Gold>
{
	friend class BaseEntity<Gold>;
public:
	Gold();
	~Gold();

protected:
	
	bool initEntity();
};

#endif