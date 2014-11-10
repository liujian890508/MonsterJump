#include "Background.h"
#include "VisibleRect.h"

#define CLOUD_NUM 2

Background::Background()
{
}


Background::~Background()
{
}

bool Background::init()
{
	auto bgSprite = Sprite::create("bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	this->initCloud();

	this->scheduleUpdate();

	return true;
}

bool Background::initCloud()
{
	Point cloudPoss[CLOUD_NUM] = {
		VisibleRect::rightTop() - Point(200, 100),
		VisibleRect::leftTop() + Point(200, -300),
	};
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		String *fileName = String::createWithFormat("cloud_%d.png", (i % 2) + 1);
		auto cloudSprite = Sprite::create(fileName->getCString());
		this->addChild(cloudSprite, 0, 100 + i);
		cloudSprite->setPosition(cloudPoss[i]);
	}
	return true;
}

void Background::update(float dt)
{
	static float offset = 5.0f;
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		auto sprite = this->getChildByTag(100 + i);
		Point newPoint = sprite->getPosition() + Point((i + offset) / 6.0f, 0);
		if ((newPoint.x - sprite->getContentSize().width / 2) > VisibleRect::right().x)
		{
			offset = CCRANDOM_0_1() * 3 + 3;
			newPoint.x = -sprite->getContentSize().width / 2;
		}
		sprite->setPosition(newPoint);
	}
}
