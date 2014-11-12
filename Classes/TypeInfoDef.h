#ifndef __TYPEINFODEF_H__
#define __TYPEINFODEF_H__

#include "cocos2d.h"
USING_NS_CC;

enum EntityType
{
	kType_Hero,
	kType_Normal,
	kType_Collapsar,
	kType_Plane,
	kType_Gold,
	kType_Bird,
	kType_Spring
};

enum MoveDir
{
	MoveDir_Up,
	MoveDir_Down,
	MoveDir_Left, 
	MoveDir_Right,
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

enum AdsResultCode
{
	ads_adView_switch = 0,
	ads_adView_success = 1,
	ads_adView_failed = 2,
	ads_spot_success = 3,
	ads_spot_failed = 4,
	ads_spot_closed = 5
};

#endif