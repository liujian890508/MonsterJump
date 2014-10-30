#ifndef __DIALOGMANAGER_H__
#define __DIALOGMANAGER_H__

#include "Singleton.h"
#include "Dialog.h"

class DialogManager: public Singleton<DialogManager>
{
public:

	
};

#define DialogMgr DialogManager::getInstance()

#endif