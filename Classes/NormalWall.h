#ifndef __NORMALWALL_H__
#define __NORMALWALL_H__

#include "BaseEntity.h"

class NormalWall: public BaseEntity<NormalWall>
{
	friend class BaseEntity<NormalWall>;
public:
	NormalWall();
	~NormalWall();

protected:

	bool initEntity();

};

#endif