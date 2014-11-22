#ifndef __BASELAYER_H__
#define __BASELAYER_H__

#include "cocos2d.h"
#include "TypeInfoDef.h"
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

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {} ;

	void addKeyboardSupport()
	{
		auto _listener = EventListenerKeyboard::create();
		_listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event){this->onKeyPressed(keycode , event);};
		_listener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event* event){this->onKeyReleased(keycode , event);};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener , this);
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