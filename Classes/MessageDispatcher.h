#ifndef __MESSAGEDISPATCHER_H__
#define __MESSAGEDISPATCHER_H__

#include <set>
#include <string>
#include "Telegram.h"
#include "Singleton.h"

class MessageListener
{
public:
	virtual int getReveiver() = 0;
	virtual bool handleMessage(const Telegram &msg) = 0;
};

class MessageDispatcher: public Singleton<MessageDispatcher>
{
private:
	std::set<Telegram> PriorityQ;

	bool DisCharge(const Telegram &msg);

	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
public:
	MessageDispatcher(){}
	~MessageDispatcher();

	void DispatchMsg(double delay,
		int	sender,
		int receiver,
		int msg,
		void* extraInfo = nullptr);

	void DispatchDelayedMessage();

	void update(float dt);
};

#define MessageDis MessageDispatcher::getInstance()

#endif