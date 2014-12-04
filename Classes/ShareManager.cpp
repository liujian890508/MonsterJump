#include "ShareManager.h"

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, Dictionary *shareInfo, Dictionary *error)
{
	switch (state)
	{
	case C2DXResponseStateBegin:
		break;
	case C2DXResponseStateSuccess:
		break;
	case C2DXResponseStateFail:
		break;
	case C2DXResponseStateCancel:
		break;
	}
	Array *errorInfo = error->allKeys();
	Object *pObj = nullptr;
	CCARRAY_FOREACH(errorInfo, pObj)
	{
		
	}
}

ShareManager::ShareManager()
{
	m_pContent = CCDictionary::create();
	m_pContent->retain();
}

ShareManager::~ShareManager()
{
	CC_SAFE_RELEASE(m_pContent);
}

void ShareManager::sendShare()
{
	C2DXShareSDK::showShareMenu(NULL, m_pContent, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	m_pContent->removeAllObjects();
}

void ShareManager::setShareAttribute(std::string key, std::string value)
{
	m_pContent->setObject(String::create(value), key);
}

void ShareManager::setDefaultContent()
{
	this->clear();
	this->setShareAttribute("content", "Catapult the box to help it go back home, Play Now!");
	this->setShareAttribute("image", "http://b383.photo.store.qq.com/psb?/V14A5Hqd22F6Vu/pLIp9K3fHiBbto0dFR49AnvxrUimMQyZhlY7DFqIlSE!/b/dH1gVeTNFgAA&bo=mACYAAAAAAADByI!&rf=viewer_4");
	this->setShareAttribute("title", "MonsterJump");
	this->setShareAttribute("description", "MonsterJump");
	this->setShareAttribute("url", "http://blog.sina.com.cn/s/blog_13e458f080102v622.html");
	this->setShareAttribute("type", std::to_string(C2DXContentTypeNews));
}

void ShareManager::initShareSDK(std::string apiID)
{
    C2DXShareSDK::open(apiID.c_str(), true);
}

void ShareManager::clear()
{
	m_pContent->removeAllObjects();
}

