#ifndef __BUYCOIN_H__
#define __BUYCOIN_H__

#include "BaseLayer.h"

class BuyCoin: public BaseLayer<BuyCoin>
{
public:
	BuyCoin();
	~BuyCoin();

	bool initBackground();

	virtual bool init();

	bool initWithMenu();

	bool initCoin();

	bool databind(void *data);

	bool handleMessage(const Telegram &msg);

private:
	EntityType		_fromLayer;
};

#endif