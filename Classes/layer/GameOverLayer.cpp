#include "GameOverLayer.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "WelcomeStoreLayer.h"
#include "VisibleRect.h"
#include "LoadingLayer.h"
#include "XmlParser.h"
#include "InGameLayer.h"
#include "WelcomeLayer.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocos2d/libiconv/include/iconv.h"
#else
#include "../../../../libiconv/include/iconv.h"
#endif
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

GameOverLayer::GameOverLayer(void) : score(0),
														     count(0),
															 bestScore(0),
															 txtDist(nullptr),
															 txtBestScore(nullptr),
															 txtScore(nullptr),
															 txt(nullptr)
{
}

GameOverLayer::~GameOverLayer(void)
{
}
bool GameOverLayer::init()
{
	Layer::init();

	auto uiWidget = GUIReader::getInstance()->widgetFromJsonFile("GameOverUI_1/GameOverUI_1.ExportJson");
	this->addChild(uiWidget);

	Button* btnBack = (Button*)uiWidget->getChildByName("btnBack");
	btnBack->setTag(BTN_REBACK);
	btnBack->addTouchEventListener(this,SEL_TouchEvent(&GameOverLayer::menuCallBack));

	Button* btnStore = (Button*)uiWidget->getChildByName("btnStore");
	btnStore->setTag(BTN_TOSTORE);
	btnStore->addTouchEventListener(this,SEL_TouchEvent(&GameOverLayer::menuCallBack));

	txtDist			=	(TextAtlas*)uiWidget->getChildByName("txtDist");
	txtBestScore	=	(TextAtlas*)uiWidget->getChildByName("txtBestScore");
	txtScore			=	(TextAtlas*)uiWidget->getChildByName("txtScore");

	int dist			= UserDefault::getInstance()->getIntegerForKey("DistCount");
	bestScore		= UserDefault::getInstance()->getIntegerForKey("bestScore");
	score			= UserDefault::getInstance()->getIntegerForKey("curScore");
	updateTextFiled(dist,txtDist);
	updateTextFiled(bestScore,txtBestScore);
	/*std::string path = FileUtils::getInstance()->getWritablePath() + "UserDefault.xml" ;
	log("%s",path.c_str());*/
	XMLParser*  mParser = XMLParser::parseWithFile("UserDefault.xml");
	String* txtCn = mParser->getString("1");
	String* txtCn1 = String::createWithFormat("%s",txtCn->getCString());
	txt = LabelTTF::create(txtCn1->getCString(),"KT",30);
	this->addChild(txt,203);
	txt->setPosition(VisibleRect::rightTop() + Point(txt->getContentSize().width/2,-200));
	txt->setColor(Color3B(255,255,10));
 	this->schedule(SEL_SCHEDULE(&GameOverLayer::runStore),1/60);
	return true;
}
Scene* GameOverLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = GameOverLayer::create();
	sc->addChild(ly);
	return sc;
}
void GameOverLayer::menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type)
{
	if (type != TouchEventType::TOUCH_EVENT_BEGAN)
	{
		return;
	}
	int tag = ((Button*)sender)->getTag();
	switch (tag)
	{
	case BTN_REBACK:
			Director::getInstance()->replaceScene(TransitionFadeDown::create(1.0f,WelcomeLayer::createScene()));
		break;
	case BTN_TOSTORE:
			Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f,WelcomeStoreLayer::createScene()));
		break;
	}
}
void GameOverLayer::runStore(float dt)
{
	if (count <= score)
	{
		count  += score /100;
		updateTextFiled(count,txtScore);
		if (count == score&&count > bestScore)
		{
		this->schedule(SEL_SCHEDULE(&GameOverLayer::showTxt),0.02f);
		UserDefault::getInstance()->setIntegerForKey("bestScore",score);
		}
	}
}
void GameOverLayer::updateTextFiled(int num,cocos2d::ui::TextAtlas* ttf)
{
	char chTxt[100];
	sprintf(chTxt,"%d",num);
	ttf->setStringValue(chTxt);
}
void GameOverLayer::showTxt(float dt)
{
		txt->setPositionX(txt->getPositionX() - 10);
		if (txt->getPositionX() <= - 260)
		{
			txt->setPositionX(-300);
		}
}