#include "Utils.h"

SpriteFrame* Utils::getSpriteFrame(std::string szSpriteFrameName)
{
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szSpriteFrameName);
	if (spriteFrame == nullptr)
	{
		auto texture2D = Director::getInstance()->getTextureCache()->addImage(szSpriteFrameName);
		auto size = texture2D->getContentSize();
		spriteFrame = SpriteFrame::createWithTexture(texture2D, Rect(0, 0, size.width, size.height));
	}
	return spriteFrame;
}

Sprite* Utils::createSprite(std::string szSpriteName)
{
	auto frame = Utils::getSpriteFrame(szSpriteName);
	if (frame == nullptr)
	{
		return Sprite::create(szSpriteName);
	}
	return Sprite::createWithSpriteFrame(frame);
}

Animate* Utils::getAnimate(std::string prefix, int begin, int end, float time)
{
	Vector<SpriteFrame*> spriteFrames;
	for (int i = begin; i < end; i++)
	{
		const char * sIndex = CCString::createWithFormat("%0.5d",i)->getCString();
		std::string fileName = prefix + sIndex + ".png";
		auto spriteFrame = Utils::getSpriteFrame(fileName);
		spriteFrames.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(spriteFrames, time);
	auto animate = Animate::create(animation);
	return animate;
}

void Utils::testRandom()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 6);

	for (int i = 0; i < 10; i++)
	{
		int num = dis(gen);
		CCLOG("%d ---------------", num);
	}

	std::tuple<int, std::string> param = std::make_tuple(1, "Hello World");
	void *data = &param;
	std::tuple<int, std::string> *result = static_cast<std::tuple<int, std::string>*>(data);
	int num = std::get<0>(*result);
	std::string str = std::get<1>(*result);
	CCLOG("%d -- %s", num, str.c_str());
}

