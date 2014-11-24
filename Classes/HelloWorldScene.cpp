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

	b2Vec2 gravity(0, 0);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(false);

	_listener = new ContactListener();
	_world->SetContactListener(_listener);

	_time = 0.0f;
	auto heroSprite = Sprite::create("map/rabbit_walk_1.png");
	this->addChild(heroSprite, 0, 1);
	heroSprite->setPosition(VisibleRect::top());
	auto seqAction = Sequence::create(
		MoveTo::create(1.5f, VisibleRect::bottom()),
		MoveTo::create(1.0f, VisibleRect::top()),
		nullptr);
	heroSprite->runAction(RepeatForever::create(seqAction));
	this->scheduleUpdate();
	addBoxBodyForSprite(heroSprite);

	auto brickSprite = Sprite::create("map/Stone elements/bg_platform_01.png");
	this->addChild(brickSprite);
	brickSprite->setPosition(VisibleRect::center());
	addBoxBodyForSprite(brickSprite);
	
    return true;
}

void HelloWorld::update(float t)
{
	if (_world)
	{
		_world->Step(t, 10, 10);
	}

	for (b2Body *body = _world->GetBodyList(); body; body = body->GetNext())
	{
		if (body->GetUserData() != nullptr)
		{
			Sprite *sprite = (Sprite*)body->GetUserData();
			b2Vec2 pt = b2Vec2((float)(sprite->getPosition().x / PT_RATIO), (float)(sprite->getPosition().y / PT_RATIO));
			float angle = (float)CC_DEGREES_TO_RADIANS(sprite->getRotation());
			body->SetTransform(pt, angle);
		}
	}
}

void HelloWorld::addBoxBodyForSprite(Sprite *sprite)
{
	b2PolygonShape polygon;
	polygon.SetAsBox((float)sprite->getContentSize().width  / PT_RATIO / 2, (float)sprite->getContentSize().height / PT_RATIO / 2);

	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &polygon;
	spriteShapeDef.density = 10;
	spriteShapeDef.isSensor = true;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float)sprite->getPositionX() / PT_RATIO, (float)sprite->getPositionY() / PT_RATIO);
	bd.userData = sprite;

	b2Body *spriteBody = _world->CreateBody(&bd);
	spriteBody->CreateFixture(&spriteShapeDef);
}
                                                                                                                                   
 
void HelloWorld::menuCloseCallback(Ref* pSender)
{

}
