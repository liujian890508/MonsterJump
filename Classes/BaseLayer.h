#ifndef __BASELAYER_H__
#define __BASELAYER_H__

#include "cocos2d.h"
USING_NS_CC;

template<class T>
class BaseLayer: public LayerColor
{
public:
	BaseLayer()
	{
	}
	virtual ~BaseLayer()
	{
	}

	virtual bool init(){ if (!LayerColor::initWithColor(Color4B(255, 0, 0, 255))) return false; return true; }
	virtual bool databind(void *data){ return true; }

	static T* create()
	{
		auto t = new (std::nothrow) T();
		if (t && t->init())
		{
			t->autorelease();
			return t;
		}
		CC_SAFE_RELEASE(t);
		return nullptr;
	}
};

#endif