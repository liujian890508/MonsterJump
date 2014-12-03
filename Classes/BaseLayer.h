#ifndef __BASELAYER_H__
#define __BASELAYER_H__

#include "cocos2d.h"
#include "TypeInfoDef.h"
#include "MessageDispatcher.h"
#include "MessageManager.h"
USING_NS_CC;

template<class T>
class BaseLayer: public Node, public MessageListener
{
protected:
	bool			m_isMessageEnabled;
	EntityType		m_entityType;
public:
	BaseLayer()
	{
		m_isMessageEnabled = false;
		m_entityType = kType_None;
	}
	virtual ~BaseLayer()
	{
		setMessageEnabled(false);
	}

	void setMessageEnabled(bool flag)
	{
		if (m_isMessageEnabled != flag)
		{
			m_isMessageEnabled = flag;
			if (m_isMessageEnabled)
			{
				MessageMgr->registerMessageHandle(this);
			}
			else
			{
				MessageMgr->removeMessageHandle(this);
			}
		}
	}

	virtual int getReveiver()
	{
		return this->m_entityType;
	}

	EntityType getEntityType(){ return m_entityType; }
	void setEntityType(EntityType type) { this->m_entityType = type; }

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
	virtual bool handleMessage(const Telegram &msg){ return true; }

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