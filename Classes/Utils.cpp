#include "Utils.h"
#include "MessageDispatcher.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
#include <jni.h>
#include "jni/JniHelper.h"
#include <android/log.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "YouMiUtil.h"
#include "IOSUtil.h"
#endif

#define PT_RATIO 32

bool Utils::_isLoad = false;

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

int Utils::getRandomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

std::string Utils::getItem(std::string key)
{
	std::string item = UserDefault::getInstance()->getStringForKey(key.c_str(), "0");
	return item;
}

void Utils::setItem(std::string key, std::string value)
{
	UserDefault::getInstance()->setStringForKey(key.c_str(), value);
}

void Utils::showLeaderboard()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSUtil::showLeaderboard();
#endif
}

void Utils::retrieveTopTenScores(std::string category)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSUtil::retrieveTopTenScores(category);
#endif
}

void Utils::reportScore(int score, std::string category)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    IOSUtil::reportScore(score, category);
#endif

}

void Utils::showCommentary()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IOSUtil::showCommentary();
#endif
}

void Utils::initGlobalConfig()
{
	Director::getInstance()->getScheduler()->scheduleUpdate(MessageDis, Scheduler::PRIORITY_SYSTEM, false);
}

void Utils::disableScreenAutoLock(bool flag)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool b = JniHelper::getStaticMethodInfo(minfo, "com/xiandiao/jump/Util", "disableScreenAutoLock", "(Z)V");
	if (!b){
		CCLOG("JniHelper::getStaticMethodInfo error...");
	}
	else{
		minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, flag);
		minfo.env->DeleteLocalRef(minfo.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	IOSUtil::disableScreenAutoLock(flag);
#endif
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

