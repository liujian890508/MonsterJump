#include "HelloWorldScene.h"
#include "VisibleRect.h"

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
    if ( !Layer::init() )
    {
        return false;
    }

	this->removeFromParent();

	auto winSize = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create("cloud_1.png");
	this->addChild(sprite);
	sprite->setPosition(winSize / 2);
	sprite->setScale(0.01f);

	auto openMenu = MenuItemFont::create("Open", [=](Ref *pSender){
		sprite->runAction(Sequence::create(
			EaseBackOut::create(ScaleTo::create(0.4f, 1.0f)),
			nullptr));
	});
	auto closeMenu = MenuItemFont::create("Close", [=](Ref *pSender){
		sprite->runAction(Sequence::create(
			EaseBackIn::create(ScaleTo::create(0.4f, 0.01f)),
			nullptr));
	});
	auto menu = Menu::create(openMenu, closeMenu, nullptr);
	this->addChild(menu);
	menu->setPosition(Point(100, 100));
	menu->alignItemsVerticallyWithPadding(30);
	
    return true;
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
