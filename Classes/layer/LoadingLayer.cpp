#include "LoadingLayer.h"
#include"layer/WelcomeLayer.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
USING_NS_CC;
using namespace cocostudio;
LoadingLayer::LoadingLayer(void) :curResLoaded(0),
													 totalResCount(7),
													 mProgress(nullptr),
													 percentage(0),
													 ttfPer(nullptr)
{
}


LoadingLayer::~LoadingLayer(void)
{
}
Scene* LoadingLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = LoadingLayer::create();
	sc->addChild(ly);
	return sc;
}
bool LoadingLayer::init()
{
	Layer::init();
	auto bg = Sprite::create("background/loading.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);

	//文本
	sprintf(chPer,"0");
	ttfPer = LabelTTF::create(chPer,"WRYH",28);
	this->addChild(ttfPer,3);
	ttfPer->setPosition(VisibleRect::center() + Point(40,-70));
	ttfPer->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	//进度条的设置
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite *one = Sprite::create("jindu.png");
	one->setPosition(Point(winSize.width / 2 + 2, winSize.height *0.2 + 3));
	this->addChild(one,0);

	//走动的进度条
	this->mProgress = ProgressTimer::create(Sprite::create("jinduOne.png"));
	mProgress->setPosition(Point(winSize.width / 2 , winSize.height *0.2));

	//设置类型
	mProgress->setType(ProgressTimerType::BAR);

	//设置精灵变化的方向
	mProgress->setBarChangeRate(Point(1,0));

	//设置精灵的起始变化的点
	mProgress->setMidpoint(Point(0,0));
	this->addChild(mProgress,1);

	auto armManager = ArmatureDataManager::getInstance();
	armManager->addArmatureFileInfoAsync("PandaAnimation/PandaAnimation.ExportJson",this,SEL_SCHEDULE(&
		LoadingLayer::armatureLoaded));
	armManager->addArmatureFileInfoAsync("pandaEffectAnimation/pandaEffectAnimation.ExportJson",this,SEL_SCHEDULE(&
		LoadingLayer::armatureLoaded));
	auto ttuCache = Director::getInstance()->getTextureCache();
	ttuCache->addImageAsync("background/background.png",CC_CALLBACK_1(LoadingLayer::textureLoaded,this));
	ttuCache->addImageAsync("background/hillViewFar.png",CC_CALLBACK_1(LoadingLayer::textureLoaded,this));
	ttuCache->addImageAsync("background/hillViewNear.png",CC_CALLBACK_1(LoadingLayer::textureLoaded,this));
	ttuCache->addImageAsync("background/treeViewFar.png",CC_CALLBACK_1(LoadingLayer::textureLoaded,this));
	ttuCache->addImageAsync("background/treeViewNear.png",CC_CALLBACK_1(LoadingLayer::textureLoaded,this));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("element.plist");

	
	return true;
}
void LoadingLayer::assetsLoaded(float dt)
{
	Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f,WelcomeLayer::createScene()));
}
void LoadingLayer::armatureLoaded(float dt)
{
	curResLoaded++;
	if (curResLoaded == totalResCount)
	{
		this->scheduleOnce(SEL_SCHEDULE(&LoadingLayer::assetsLoaded),0.0f);
	}
}
void LoadingLayer::textureLoaded(cocos2d::Texture2D* ttu2D)
{
	curResLoaded++;

	//获取加载的图片总数的百分比
	percentage =  curResLoaded/(float)totalResCount * 100;
	log("%f",percentage);
	//更新文本
	sprintf(chPer,"%.1f%s",percentage,"%");
	ttfPer->setString(chPer);

	//设置进度条显示比例
	mProgress->setPercentage(percentage);

	
	if (curResLoaded == totalResCount)
	{
		this->scheduleOnce(SEL_SCHEDULE(&LoadingLayer::assetsLoaded),2.0f);
	}
}