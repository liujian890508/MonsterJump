#ifndef __WELCOMELAYER_H__
#define __WELCOMELAYER_H__

#include "BaseLayer.h"

class HomeLayer : public BaseLayer<HomeLayer>
{
public:
	HomeLayer();
	virtual ~HomeLayer();

	bool init();
	bool initOther();
	bool initRole();
	bool loadResource();

	bool initTest();
	
	void playLogoAni();

	bool handleMessage(const Telegram &msg);
};

#endif