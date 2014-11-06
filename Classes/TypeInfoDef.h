#ifndef __TYPEINFODEF_H__
#define __TYPEINFODEF_H__

#include "cocos2d.h"
#include "NormalWall.h"
USING_NS_CC;

typedef std::vector<NormalWall*> NormalVector;
typedef NormalVector::iterator NormalVectorIt;

typedef std::vector<experimental::TMXTiledMap*> MapVector;
typedef MapVector::iterator MapVectorIt;

enum MoveDir
{
	MoveDir_Up,
	MoveDir_Down,
	MoveDir_None
};

enum DialogEvent
{
	Event_show,
	Event_hide
};

enum HeroState
{
	kState_fall,
	kState_jump,
	kState_rush,
	kState_rush_end,
	kState_walk
};

#endif