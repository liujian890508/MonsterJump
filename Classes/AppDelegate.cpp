#include "AppDelegate.h"
#include "HomeLayer.h"
#include "Utils.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("MonsterJump", Rect(0, 0, 320, 480));
        director->setOpenGLView(glview);
    }

	auto frameSize = Director::getInstance()->getVisibleSize();

	auto lsSize = Size(640, 960);
	float scaleX = frameSize.width / lsSize.width;
	float scaleY = frameSize.height / lsSize.height;

	float scale_width = 0.0f, scale_height = 0.0f;
	if (scaleX > scaleY)
		scale_width = scaleX / (frameSize.height / lsSize.height);
	else
		scale_width = scaleX / (frameSize.width / lsSize.width);

	if (scaleX > scaleY)
		scale_height = scaleY / (frameSize.height / lsSize.height);
	else
		scale_height = scaleY / (frameSize.width / lsSize.width);

	float scale = std::max(scale_width, scale_height);
	
	glview->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	Utils::testRandom();

	Utils::replaceScene(HomeLayer::create());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
