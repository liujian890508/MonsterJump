#include "ContactListener.h"


ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	BaseSprite *spriteA = (BaseSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	BaseSprite *spriteB = (BaseSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
	spriteA->BeginContact(contact, spriteB);
	spriteB->BeginContact(contact, spriteA);
}

void ContactListener::EndContact(b2Contact* contact)
{
	BaseSprite *spriteA = (BaseSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	BaseSprite *spriteB = (BaseSprite*)contact->GetFixtureB()->GetBody()->GetUserData();
	spriteA->BeginContact(contact, spriteB);
	spriteB->BeginContact(contact, spriteA);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CCLOG("--------------------------------------PreSolve");
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	CCLOG("--------------------------------------PostSolve");
}