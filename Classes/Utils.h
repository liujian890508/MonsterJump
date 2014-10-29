#ifndef __UTILS_H__
#define __UTILS_H__

#include "BaseLayer.h"

class Utils
{
public:
	template<typename T>
	static void replaceScene(BaseLayer<T> *layer, void *data = nullptr);
};

template<typename T>
void Utils::replaceScene(BaseLayer<T> *layer, void *data)
{
	auto scene = Scene::create();
	if (scene && layer)
	{
		scene->addChild(layer);
		auto director = Director::getInstance();
		auto oldScene = director->getRunningScene();
		if (oldScene)
		{
			director->replaceScene(scene);
		}
		else
		{
			director->runWithScene(scene);
		}
		layer->databind(data);
	}
}

#endif