#ifndef __BASELAYER_H__
#define __BASELAYER_H__

#include "cocos2d.h"
USING_NS_CC;

template<class T>
class BaseLayer: public Node
{
public:
	BaseLayer()
	{
	}
	virtual ~BaseLayer()
	{
	}

	virtual bool init(){ return true; }
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