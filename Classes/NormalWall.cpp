#include "NormalWall.h"


NormalWall::NormalWall()
{
}


NormalWall::~NormalWall()
{
}

bool NormalWall::initEntity()
{
    setEntityType(EntityType::kType_Normal);
	return true;
}
