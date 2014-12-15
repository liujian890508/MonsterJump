#ifndef __MESSAGEMANAGER_H__
#define __MESSAGEMANAGER_H__

#include <map>
#include "MessageDispatcher.h"
#include "Singleton.h"

class MessageManager: public Singleton<MessageManager>
{
	friend class Singleton<MessageManager>;
	typedef std::map<int, MessageListener*> MessageListenerMap;
	typedef MessageListenerMap::iterator MessageListenerIt;
private:
	MessageListenerMap		_listenerMap;
private:
	MessageManager(){}
	MessageManager(const MessageManager&);
	MessageManager& operator=(const MessageManager&);
public:
	~MessageManager();

	void registerMessageHandle(MessageListener *listener);
	MessageListener* getListenerById(int id);
	void removeMessageHandle(int id);
	void removeMessageHandle(MessageListener *listener);
	void removeAllListener();
	int getSize(){ return _listenerMap.size(); }
	MessageListenerMap *getAllListener(){ return &_listenerMap; }
};

#define MessageMgr MessageManager::getInstance()

#endif