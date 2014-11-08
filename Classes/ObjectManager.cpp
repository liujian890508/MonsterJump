#include "ObjectManager.h"


void ObjectManager::put(BaseSprite* t)
{
	_allObjects.push_back(t);
}

BaseSprite* ObjectManager::get(int i)
{
	return _allObjects[i];
}

std::vector<BaseSprite*> ObjectManager::getAllObject()
{
	return _allObjects;
}

size_t ObjectManager::size()
{
	return _allObjects.size();
}

void ObjectManager::clear()
{
	return _allObjects.clear();
}

void ObjectManager::remove(int i)
{
	std::vector<BaseSprite*>::iterator it = _allObjects.begin() + i;
	if (it != _allObjects.end())
	{
		_allObjects.erase(it);
	}
}

void ObjectManager::remove(BaseSprite* entity)
{

}