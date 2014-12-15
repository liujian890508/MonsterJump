#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "Singleton.h"
#include "TypeInfoDef.h"
#include "BaseSprite.h"

class ObjectManager: public Singleton<ObjectManager>
{
	friend class Singleton<ObjectManager>;
private:
	ObjectManager(){}
	ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);
public:
	~ObjectManager(){};

	void put(BaseSprite* t);

	BaseSprite* get(int i);

	std::vector<BaseSprite*> getAllObject();

	size_t size();

	void remove(int i);

	void remove(BaseSprite* entity);

	void clear();

private:
	std::vector<BaseSprite*> _allObjects;
};

#define ObjectMgr ObjectManager::getInstance()

#endif