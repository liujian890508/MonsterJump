#ifndef __UTILS_H__
#define __UTILS_H__

#include "BaseLayer.h"

class Utils
{
public:
	template<typename T>
	static void replaceScene(BaseLayer<T> *layer, void *data = nullptr);

	static SpriteFrame* getSpriteFrame(std::string szSpriteFrameName);

	static Sprite* createSprite(std::string szSpriteName);

	static void testRandom();
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
		if (oldScene && layer->databind(data))
			director->replaceScene(scene);
		else
			director->runWithScene(scene);
	}
}

#endif