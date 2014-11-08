#ifndef __COLLAPSAR_H__
#define __COLLAPSAR_H__

#include "BaseEntity.h"

class Collapsar: public BaseEntity<Collapsar>
{
	friend class BaseEntity<Collapsar>;
public:
	Collapsar();
	~Collapsar();

protected:
	bool initEntity();
};

#endif