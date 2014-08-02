#include "AppDelegate.h"
#include "layer/LoadingLayer.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if(!glview) {
#ifdef _WIN32
		glview = GLView::createWithRect("My Game",Rect(0,0,800,480));
#else
		//获取屏幕分辨率
		auto screen	=	glview->getFrameSize();
		glview = GLView::createWithRect("My Game",Rect(0,0,screen.width,screen.height));
#endif // _WIN32
		director->setOpenGLView(glview);
	}
	glview->setDesignResolutionSize(800,480,ResolutionPolicy::EXACT_FIT);
	director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = LoadingLayer::createScene();

    // run
    director->runWithScene(scene);

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
