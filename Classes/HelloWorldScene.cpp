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

	auto wallSprite = Sprite::create("elementStone013.png");
	this->addChild(wallSprite);
	wallSprite->setPosition(VisibleRect::center());

	auto boxSprite = Sprite::create("avatar_01.png");
	this->addChild(boxSprite);
	boxSprite->setPosition(wallSprite->getPosition() + Point(0, wallSprite->getContentSize().height / 2 + boxSprite->getContentSize().height / 2));
	boxSprite->runAction(RepeatForever::create( Sequence::create(
		JumpBy::create(1.3, Point(0, 0), 300, 1),
		nullptr)));
    
    return true;
}
                                                                                                                                   
 
void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
