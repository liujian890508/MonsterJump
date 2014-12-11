#ifndef __UTILS_H__
#define __UTILS_H__

#include "BaseLayer.h"
#include "BaseSprite.h"

class Utils
{
public:
	template<typename T>
	static void replaceScene(BaseLayer<T> *layer, void *data = nullptr);
	static SpriteFrame* getSpriteFrame(std::string szSpriteFrameName);
	static Sprite* createSprite(std::string szSpriteName);
	static Animate* getAnimate(std::string prefix, int begin, int end, float time = 0.1f);
	static int getRandomInt(int min, int max);
	static void testRandom();

	static std::string getItem(std::string key);
	static void setItem(std::string key, std::string value);
    
    static void showLeaderboard();
    static void retrieveTopTenScores(std::string category);
    static void reportScore(int score, std::string category);

	static void initGlobalConfig();
	static void disableScreenAutoLock(bool flag);
	static std::string getUniquelyIdentifies();

private:
	static bool		_isLoad;
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
		auto aniScene = TransitionPageTurn::create(0.5f, scene, true);
		if (oldScene && layer->databind(data))
			director->replaceScene(aniScene);
		else
			director->runWithScene(scene);
	}
}

#endif