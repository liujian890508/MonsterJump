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

private:
	LayerName		_fromLayer;
};

#endif