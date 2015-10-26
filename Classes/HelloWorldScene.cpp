#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "PluginManager.h"
#include "PluginProtocol.h"
#include "ui/UILayout.h"
#include "ui/UIRichText.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
#include <jni.h>
#include "jni/JniHelper.h"
#include <android/log.h>
#include "PluginJniHelper.h"
#endif

using namespace ui;
using namespace plugin;
USING_NS_CC;

#define PT_RATIO 32

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
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();
	auto camera = Camera::createPerspective(60, (float)size.width / size.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);
	this->setCameraMask(2);

	auto sprite = Sprite::create("rabbit_walk_1.png");
	this->addChild(sprite);
	sprite->setPosition(size / 2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	float zEye = Director::getInstance()->getZEye();

    return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("--------------------------onTouchBegan");
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	CCLOG("--------------------------onTouchEnded");
}

void HelloWorld::update(float t)
{
	
}

void HelloWorld::addBoxBodyForSprite(Sprite *sprite)
{
	
}
                                                                                                                                   
 
void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
