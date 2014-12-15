#ifndef __SHAREMANAGER_H__
#define __SHAREMANAGER_H__

#include "Singleton.h"
#include "C2DXShareSDK.h"
using namespace cn::sharesdk;

class ShareManager: public Singleton<ShareManager>
{
	friend class Singleton<ShareManager>;
private:
	ShareManager();
	ShareManager(const ShareManager&);
	ShareManager& operator=(const ShareManager&);
public:
	~ShareManager();
	void setShareAttribute(std::string key, std::string value);
	void sendShare();
	void setDefaultContent();
    void initShareSDK(std::string apiID);
	void clear();

private:
	Dictionary		*m_pContent;
};

#define ShareMgr ShareManager::getInstance()

#endif