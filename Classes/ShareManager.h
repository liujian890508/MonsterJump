#ifndef __SHAREMANAGER_H__
#define __SHAREMANAGER_H__

#include "Singleton.h"
#include "C2DXShareSDK.h"
using namespace cn::sharesdk;

class ShareManager: public Singleton<ShareManager>
{
public:
	ShareManager();
	~ShareManager();
	void setShareAttribute(std::string key, std::string value);
	void sendShare();
	void setDefaultContent();

private:
	Dictionary		*m_pContent;
};

#define ShareMgr ShareManager::getInstance()

#endif