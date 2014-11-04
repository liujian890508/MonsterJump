#include "HelloWorldScene.h"
#include "VisibleRect.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	_time = 0.0f;
	auto heroSprite = Sprite::create("map/avatar_01.png");
	this->addChild(heroSprite, 0, 1);
	heroSprite->setPosition(VisibleRect::center());
	this->scheduleUpdate();
	
    return true;
}

void HelloWorld::update(float t)
{
	_time += t * 3;
	float v = 150.0f;
	float a = -58.0f;
	float s = v * _time + a * _time * _time / 2;
	auto node = this->getChildByTag(1);
	node->setPositionY(VisibleRect::center().y + s);

	if (node->getPositionY() < 0)
	{
		node->setPosition(VisibleRect::center());
		_time = 0.0f;
	}
}
                                                                                                                                   
 
void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
