#ifndef __STORE_H__
#define __STORE_H__

#include "BaseLayer.h"

class Store: public BaseLayer<Store>
{
public:
	Store();
	~Store();

	virtual bool init();

	bool initWithMenu();

	bool initCoin();
};

#endif