#include "MessageManager.h"


MessageManager::~MessageManager()
{
}

void MessageManager::registerMessageHandle(MessageListener *listener)
{
	MessageListener *msgListener = this->getListenerById(listener->getReveiver());
	if (msgListener != nullptr)
	{
		this->removeMessageHandle(msgListener);
	}
	_listenerMap.insert(std::make_pair(listener->getReveiver(), listener));
}

MessageListener* MessageManager::getListenerById(int id)
{
	MessageListenerIt it = _listenerMap.find(id);
	if (it != _listenerMap.end())
	{
		return it->second;
	}
	return nullptr;
}

void MessageManager::removeMessageHandle(int id)
{
	MessageListenerIt it = _listenerMap.find(id);
	if (it != _listenerMap.end())
	{
		_listenerMap.erase(it);
	}
}

void MessageManager::removeMessageHandle(MessageListener *listener)
{
	removeMessageHandle(listener->getReveiver());
}

void MessageManager::removeAllListener()
{
	_listenerMap.clear();
}