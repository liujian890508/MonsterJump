#include "MessageDispatcher.h"
#include "MessageManager.h"
#include <ctime>
#include "Utils.h"

MessageDispatcher::~MessageDispatcher()
{
	PriorityQ.clear();
}

bool MessageDispatcher::DisCharge(const Telegram &msg)
{
	if (msg.Receiver == -1)
	{
		auto allListener = MessageMgr->getAllListener();
		for (auto it = allListener->begin(); it != allListener->end(); it++)
		{
			MessageListener *pReceiver = it->second;
			if (pReceiver->handleMessage(msg)) break;
		}
	}
	else
	{
		MessageListener* pReceiver = MessageMgr->getListenerById(msg.Receiver);
		if (pReceiver != nullptr)
			pReceiver->handleMessage(msg);
	}
	return true;
}

void MessageDispatcher::DispatchMsg(double delay,
	int	sender,
	int receiver,
	int msg,
	void* extraInfo)
{
	Telegram telegram(sender, receiver, msg, delay, extraInfo);
	if (delay <= 0.0)
	{
		DisCharge(telegram);
	}
	else
	{
		double current = clock() / 1000 + delay;
		telegram.DispatchTime = current;
		PriorityQ.insert(telegram);
	}
}

void MessageDispatcher::DispatchDelayedMessage()
{
	double current = clock() / 1000;
	while (!PriorityQ.empty() &&
		PriorityQ.begin()->DispatchTime < current &&
		PriorityQ.begin()->DispatchTime > 0)
	{
		const Telegram& telegram = *PriorityQ.begin();
		this->DisCharge(telegram);
		PriorityQ.erase(PriorityQ.begin());
	}
}

void MessageDispatcher::update(float dt)
{
	this->DispatchDelayedMessage();
}
