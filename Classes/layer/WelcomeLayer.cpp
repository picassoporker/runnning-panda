#include "WelcomeLayer.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "InGameLayer.h"
#include "WelcomeStoreLayer.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;


WelcomeLayer::WelcomeLayer(void) :mBackground(nullptr)
{
}

WelcomeLayer::~WelcomeLayer(void)
{
}
Scene* WelcomeLayer::createScene()
{
	auto sc = Scene::create();
	auto ly  = WelcomeLayer::create();
	sc->addChild(ly);
	return sc;
}
bool WelcomeLayer::init()
{
	Layer::init(); 

	Sprite* bg = Sprite::create("background/background.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);

	mBackground = BackGroundLayer::create();
	this->addChild(mBackground);
	mBackground->setAnchorPoint(Point::ZERO);

	auto uiWidget = GUIReader::getInstance()->widgetFromJsonFile("WelcomeLayerUI/WelcomeLayerUI.ExportJson");
	this->addChild(uiWidget);

	Button* btnStart = (Button*)uiWidget->getChildByName("btnStart");
	Button* btnOption = (Button*)uiWidget->getChildByName("btnOption");
	Button* btnRank = (Button*)uiWidget->getChildByName("btnRank");
	Button* btnHelp = (Button*)uiWidget->getChildByName("btnHelp");
	Button* btnStore = (Button*)uiWidget->getChildByName("btnStore");

	btnStart->addTouchEventListener(this,SEL_TouchEvent(&WelcomeLayer::menuCallBack));
	btnOption->addTouchEventListener(this,SEL_TouchEvent(&WelcomeLayer::menuCallBack));
	btnRank->addTouchEventListener(this,SEL_TouchEvent(&WelcomeLayer::menuCallBack));
	btnHelp->addTouchEventListener(this,SEL_TouchEvent(&WelcomeLayer::menuCallBack));
	btnStore->addTouchEventListener(this,SEL_TouchEvent(&WelcomeLayer::menuCallBack));

	createGameXml();
	
	return true;
}

void WelcomeLayer::onEnterTransitionDidFinish()
{
	this->schedule(SEL_SCHEDULE(&WelcomeLayer::gameStep),0.02f);
}
void WelcomeLayer::gameStep(float dt)
{
	mBackground->move(10);
}
void WelcomeLayer::menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type)
{
	if (type != TouchEventType::TOUCH_EVENT_BEGAN)
	{
		return;
	}
	int tag = ((Widget*)sender)->getTag();
	switch (tag)
	{
	case BTN_START:
		Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f,InGameLayer::createScene()));
		break;
	case BTN_OPTION:
		break;
	case BTN_RANK:
		break;
	case BTN_HELP:
		break;
	case BTN_STORE:
		Director::getInstance()->replaceScene(TransitionFadeDown::create(0.05f,WelcomeStoreLayer::createScene()));
		break;
	}
}
void WelcomeLayer::createGameXml()
{
	std::string filePath						= FileUtils::getInstance()->getWritablePath() + "UserDefault.xml";
	if (FileUtils::getInstance()->isFileExist(filePath))
	{
		return;
	}
	//tinyxml2::XMLDocument* pDoc	= new tinyxml2::XMLDocument();
	////XML声明
	//XMLDeclaration* pDel				= pDoc->NewDeclaration("xml version = \"1.0\" encoding = \"UTF-8\"");
	//pDoc->LinkEndChild(pDel);
	////创建根路径
	//XMLElement* root						=	pDoc->NewElement("pandaData");
	//root->SetAttribute("version","1.0");
	//pDoc->LinkEndChild(root);
	////注释
	//XMLComment* pCom					=	pDoc->NewComment("尼玛，这是熊猫的游戏数据，老子正在苦逼创造，蛋疼");
	//root->LinkEndChild(pCom);
	////创建子节点
	//XMLElement* bamboo				=	pDoc->NewElement("bamboo");
	//bamboo->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(bamboo);
	//XMLElement* hongZhong			=	pDoc->NewElement("hongZhong");
	//hongZhong->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(hongZhong);
	//XMLElement* jiu							=	pDoc->NewElement("jiu");
	//jiu->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(jiu);
	//XMLElement* DefensiveCover		=	pDoc->NewElement("DefensiveCover");
	//DefensiveCover->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(DefensiveCover);
	//XMLElement* DistCount				=	pDoc->NewElement("DistCount");
	//DistCount->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(DistCount);
	//XMLElement* bestScore				=	pDoc->NewElement("bestScore");
	//bestScore->LinkEndChild(pDoc->NewText("0"));
	//root->LinkEndChild(bestScore);
	//pDoc->SaveFile(filePath.c_str());
	//pDoc->Print();
	//delete pDoc;

	UserDefault::getInstance()->setIntegerForKey("bamboo",0);
	UserDefault::getInstance()->setIntegerForKey("zhong",0);
	UserDefault::getInstance()->setIntegerForKey("jiu",0);
	UserDefault::getInstance()->setIntegerForKey("DefensiveCover",0);
	UserDefault::getInstance()->setIntegerForKey("DistCount",0);
	UserDefault::getInstance()->setIntegerForKey("bestScore",0);
	UserDefault::getInstance()->setIntegerForKey("curScore",0);
	UserDefault::getInstance()->flush();
}