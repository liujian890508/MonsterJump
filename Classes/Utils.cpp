#include "Utils.h"
#include "MessageDispatcher.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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

void Utils::createPhysicsBox(BaseSprite *sprite, b2World *world)
{
	b2PolygonShape polygon;
	polygon.SetAsBox((float)sprite->getContentSize().width / PT_RATIO / 2, (float)sprite->getContentSize().height / PT_RATIO / 2);

	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &polygon;
	spriteShapeDef.density = 10.f;
	spriteShapeDef.isSensor = true;   // 对象之间有碰撞检测但是又不想让它们有碰撞反应

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)(sprite->getPosition().x / PT_RATIO),
		(float)(sprite->getPosition().y / PT_RATIO));
	bd.userData = sprite;

	b2Body* spriteBody = world->CreateBody(&bd);
	spriteBody->CreateFixture(&spriteShapeDef);
}

b2Vec2 Utils::cocosConverToB2(Point point)
{
	b2Vec2 pt = b2Vec2((float)(point.x / PT_RATIO), (float)(point.y / PT_RATIO));
	return pt;
}

void Utils::lazyInit()
{
	
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
	
}

void Utils::initGlobalConfig()
{
	Director::getInstance()->getScheduler()->scheduleUpdate(MessageDis, Scheduler::PRIORITY_SYSTEM, false);
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

