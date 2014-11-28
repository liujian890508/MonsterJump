#include "ResultLayer.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
using namespace ui;
using namespace cocostudio;

ResultLayer::ResultLayer()
{
}


ResultLayer::~ResultLayer()
{
}

bool ResultLayer::init()
{
	auto bgSprite = Sprite::create("ui/ui_bg.png");
	this->addChild(bgSprite);
	bgSprite->setPosition(VisibleRect::center());

	auto rect = VisibleRect::getVisibleRect();
	float scaleX = rect.size.width / bgSprite->getContentSize().width;
	float scaleY = rect.size.height / bgSprite->getContentSize().height;
	bgSprite->setScaleX(scaleX);
	bgSprite->setScaleY(scaleY);

	auto widget = GUIReader::getInstance()->widgetFromJsonFile("ui/UI_Result.json");
	widget->setPosition(VisibleRect::center());
	widget->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(widget);
	return true;
}

bool ResultLayer::databind(void *data)
{

	return true;
}
