#include "Utils.h"

SpriteFrame* Utils::getSpriteFrame(std::string szSpriteFrameName)
{
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szSpriteFrameName);
	if (spriteFrame == nullptr)
	{
		auto texture2D = Director::getInstance()->getTextureCache()->addImage(szSpriteFrameName);
		auto size = texture2D->getContentSize();
		spriteFrame = SpriteFrame::createWithTexture(texture2D, Rect(0, 0, size.width, size.height));
	}
	return spriteFrame;
}

Sprite* Utils::createSprite(std::string szSpriteName)
{
	auto frame = Utils::getSpriteFrame(szSpriteName);
	if (frame == nullptr)
	{
		return Sprite::create(szSpriteName);
	}
	return Sprite::createWithSpriteFrame(frame);
}

