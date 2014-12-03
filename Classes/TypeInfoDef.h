#ifndef __TYPEINFODEF_H__
#define __TYPEINFODEF_H__

#include "cocos2d.h"
USING_NS_CC;

enum EntityType
{
	kType_None			= -1,
	kType_Hero			= 1,
	kType_Normal		= 2,
	kType_Collapsar		= 3,
	kType_Plane			= 4,
	kType_Gold			= 5,
	kType_Bird			= 6,
	kType_Spring		= 7,
	kType_Home			= 8,
	kType_BuyCoin		= 9,
	kType_GameWorld		= 10,
	kType_Setting		= 11,
	kType_Store			= 12
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
	ads_spot_closed = 5,
	ads_offers_closed = 6
};

#endif