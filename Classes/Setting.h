#ifndef __SETTING_H__
#define __SETTING_H__

#include "BaseLayer.h"

class Setting: public BaseLayer<Setting>
{
public:
	Setting();
	~Setting();

	virtual bool init();

	bool initWithMenu();

	bool initCoin();

	virtual bool handleMessage(const Telegram &msg);
};

#endif