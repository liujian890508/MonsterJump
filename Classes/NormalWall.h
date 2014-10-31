#ifndef __NORMALWALL_H__
#define __NORMALWALL_H__

#include "BaseEntity.h"

class NormalWall: public BaseEntity<NormalWall>
{
public:
	NormalWall();
	~NormalWall();

	virtual bool initEntity();

};

#endif