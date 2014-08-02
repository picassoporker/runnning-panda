#include "WelcomeStoreLayer.h"
#include "cocos/ui/CocosGUI.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "WelcomeLayer.h"
using namespace cocostudio;
USING_NS_CC;
using namespace ui;
WelcomeStoreLayer::WelcomeStoreLayer(void) :	btnBuyFang(nullptr),
																			btnBuyJiu(nullptr),
																			btnBuyZhong(nullptr),
																			btnReback(nullptr),
																			txtJiu(nullptr),
																			txtZhong(nullptr),
																			txtBao(nullptr),
																			txtZhu(nullptr),
																			JIU_PRICE(5),
																			BAO_PRICE(10),
																			ZHONG_PRICE(2),
																			CaheBao(0),
																			CaheZhong(0),
																			CaheJiu(0),
																			Cahezhu(0)
{
}


WelcomeStoreLayer::~WelcomeStoreLayer(void)
{
}

Scene* WelcomeStoreLayer::createScene()
{
	auto sc		=	Scene::create();
	auto ly		=	WelcomeStoreLayer::create();
	sc->addChild(ly);

	return sc;
}
bool WelcomeStoreLayer::init()
{
	Layer::init();
	auto uiWidget = GUIReader::getInstance()->widgetFromJsonFile("WelcomeStoreUI_1/WelcomeStoreUI_1.ExportJson");
	this->addChild(uiWidget);

	Button* btnBuyZhong = (Button*)uiWidget->getChildByName("btnBuyZhong");
	Button* btnBuyJiu = (Button*)uiWidget->getChildByName("btnBuyJiu");
	Button* btnBuyFang = (Button*)uiWidget->getChildByName("btnBuyFang");
	Button* btnReback = (Button*)uiWidget->getChildByName("btnReback");

	btnBuyZhong->setTag(BUTTON_TAG_ZHONG);
	btnBuyFang->setTag(BUTTON_TAG_BAO);
	btnBuyJiu->setTag(BUTTON_TAG_JIU);
	btnReback->setTag(BUTTON_TAG_REBACK);


	btnBuyZhong->addTouchEventListener(this,SEL_TouchEvent(&WelcomeStoreLayer::menuCallBack));
	btnBuyFang->addTouchEventListener(this,SEL_TouchEvent(&WelcomeStoreLayer::menuCallBack));
	btnBuyJiu->addTouchEventListener(this,SEL_TouchEvent(&WelcomeStoreLayer::menuCallBack));
	btnReback->addTouchEventListener(this,SEL_TouchEvent(&WelcomeStoreLayer::menuCallBack));

	txtJiu = (TextAtlas*)uiWidget->getChildByName("txtJiu");
	txtZhong = (TextAtlas*)uiWidget->getChildByName("txtZhong");
	txtBao = (TextAtlas*)uiWidget->getChildByName("txtFang");
	txtZhu = (TextAtlas*)uiWidget->getChildByName("txtZhu");

	readXml();
	updateCahe(CaheBao,txtBao);
	updateCahe(CaheZhong,txtZhong);
	updateCahe(CaheJiu,txtJiu);
	updateCahe(Cahezhu,txtZhu);
	return true;
}
void WelcomeStoreLayer::readXml()
{
	Cahezhu = UserDefault::getInstance()->getIntegerForKey("bamboo");
	CaheBao = UserDefault::getInstance()->getIntegerForKey("DefensiveCover");
	CaheJiu = UserDefault::getInstance()->getIntegerForKey("jiu");
	CaheZhong = UserDefault::getInstance()->getIntegerForKey("zhong");
}
void WelcomeStoreLayer::updateCahe(int Cahe,cocos2d::ui::TextAtlas* ttf)
{
	char chCahe[10];
	sprintf(chCahe,"%d",Cahe);
	ttf->setStringValue(chCahe);
}
void WelcomeStoreLayer::updateTextFiled(int& data,int cost ,cocos2d::ui::TextAtlas* ttf)
{
	if (Cahezhu - cost  < 0)
	{
		MessageBox("抱歉！金钱不足","温馨提示");
		return;
	}
	Cahezhu  -= cost;
	data		  += 1;
	char chData[32];
	sprintf(chData,"%d",data);
	ttf->setStringValue(chData);
	updateCahe(Cahezhu,txtZhu);
	UserDefault::getInstance()->setIntegerForKey("bamboo",Cahezhu);
	UserDefault::getInstance()->setIntegerForKey("zhong",CaheZhong);
	UserDefault::getInstance()->setIntegerForKey("jiu",CaheJiu);
	UserDefault::getInstance()->setIntegerForKey("DefensiveCover",CaheBao);
}


void WelcomeStoreLayer::menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type)
{
	if (type != TouchEventType::TOUCH_EVENT_BEGAN)
	{
		return;
	}
	int tag = ((Button*)sender)->getTag();
	switch (tag)
	{
	case BUTTON_TAG_JIU:
		updateTextFiled(CaheJiu,JIU_PRICE,txtJiu);
		break;
	case BUTTON_TAG_ZHONG:
		updateTextFiled(CaheZhong,ZHONG_PRICE,txtZhong);
		break;
	case BUTTON_TAG_BAO:
		updateTextFiled(CaheBao,BAO_PRICE,txtBao);
		break;
	case BUTTON_TAG_REBACK:
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.05f,WelcomeLayer::createScene()));
		break;
	}
}
