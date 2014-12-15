#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "Singleton.h"
#include "Dialog.h"

class DialogManager: public Singleton<DialogManager>
{
	friend class Singleton<DialogManager>;
private:
	DialogManager(){}
	DialogManager(const DialogManager&);
	DialogManager& operator=(const DialogManager&);
public:
	~DialogManager(){}
	
};

#define DialogMgr DialogManager::getInstance()

#endif