#ifndef __PLANE_H__
#define __PLANE_H__

#include "BaseEntity.h"

class Plane : public BaseEntity<Plane>
{
	friend class BaseEntity<Plane>;
public:
	Plane();
	~Plane();

protected:

	bool initEntity();
};

#endif