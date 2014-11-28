#ifndef __RESULTLAYER_H__
#define __RESULTLAYER_H__

#include "BaseLayer.h"

class ResultLayer: public BaseLayer<ResultLayer>
{
public:
	ResultLayer();
	~ResultLayer();

	bool init();

	bool databind(void *data);
};

#endif