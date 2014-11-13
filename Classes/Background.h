#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "BaseLayer.h"

class Background: public BaseLayer<Background>
{
public:
	Background();
	~Background();

	bool init();

	void update(float dt);

	bool initCloud();

	void move(Point point);

private:

};

#endif