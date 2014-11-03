#ifndef __TYPEINFODEF_H__
#define __TYPEINFODEF_H__

#include "NormalWall.h"

typedef std::vector<NormalWall*> NormalVector;
typedef NormalVector::iterator NormalVectorIt;

enum MoveDir
{
	MoveDir_Up,
	MoveDir_Down,
	MoveDir_None
};

#endif