#include "GameStoreLayer.h"
#include "cocos/editor-support//cocostudio/CocoStudio.h"
#include "InGameLayer.h"
using namespace cocostudio;
USING_NS_CC;
using namespace ui;
GameStoreLayer::GameStoreLayer(void) :clip(nullptr)
															,winSize(0,0)
															,reBack(false),
															JIU_PRICE(0),
															ZHONG_PRICE(0),
															BAO_PRICE(0),
															CaheBao(0),
															CaheZhong(0),
															CaheJiu(0),
															Cahezhu(0),
															txtJiu(nullptr),
															txtZhong(nullptr),
															txtBao(nullptr)
{
}


GameStoreLayer::~GameStoreLayer(void)
{
}
bool GameStoreLayer::init()
{
	Layer::init();
	winSize = Director::getInstance()->getVisibleSize();
	//创建裁剪点
	clip		=	ClippingNode::create();
	clip->setInverted(true);
	clip->setAlphaThreshold(0);
	this->addChild(clip);
	clip->setAnchorPoint(Point::ZERO);
	LayerColor* back = LayerColor::create(Color4B(0,0,0,110));
	clip->addChild(back);

	//以下模型是带图像遮罩
	Node* nodef=Node::create();//图像的节点
	Sprite* close=Sprite::create("clipbg.png");
	nodef->addChild(close);
	nodef->setPosition(winSize.width/2,winSize.height/2);
	clip->setStencil(nodef);
	//加载商城
	auto storeWidget	=	GUIReader::getInstance()->widgetFromJsonFile("StoreUI_1/StoreUI_1.ExportJson");
	this->addChild(storeWidget);

	Button* btnReback = (Button*)storeWidget->getChildByName("btnReback");
	Button* btnBuyZhong = (Button*)storeWidget->getChildByName("btnBuyZhong");
	Button* btnBuyFang = (Button*)storeWidget->getChildByName("btnBuyFang");
	Button* btnBuyJiu = (Button*)storeWidget->getChildByName("btnBuyJiu");
	Button* btnBuyMore = (Button*)storeWidget->getChildByName("btnBuyMore");

	btnReback->addTouchEventListener(this,SEL_TouchEvent(&GameStoreLayer::menuCallBack));
	btnBuyZhong->addTouchEventListener(this,SEL_TouchEvent(&GameStoreLayer::menuCallBack));
	btnBuyFang->addTouchEventListener(this,SEL_TouchEvent(&GameStoreLayer::menuCallBack));
	btnBuyJiu->addTouchEventListener(this,SEL_TouchEvent(&GameStoreLayer::menuCallBack));
	btnBuyMore->addTouchEventListener(this,SEL_TouchEvent(&GameStoreLayer::menuCallBack));

	btnReback->setTag(GAME_BTN_REBACK);
	btnBuyZhong->setTag(GAME_BTN_BUYZHOGN);
	btnBuyFang->setTag(GAME_BTN_FANG);
	btnBuyJiu->setTag(GAME_BTN_JIU);
	btnBuyMore->setTag(GAME_BTN_MORE);

	txtJiu = (TextAtlas*)storeWidget->getChildByName("txtJiu");
	txtZhong = (TextAtlas*)storeWidget->getChildByName("txtZhong");
	txtBao = (TextAtlas*)storeWidget->getChildByName("txtFang");

	Cahezhu = UserDefault::getInstance()->getIntegerForKey("bamboo");
	CaheBao = UserDefault::getInstance()->getIntegerForKey("DefensiveCover");
	CaheJiu = UserDefault::getInstance()->getIntegerForKey("jiu");
	CaheZhong = UserDefault::getInstance()->getIntegerForKey("zhong");

	updateCahe(CaheBao,txtBao);
	updateCahe(CaheZhong,txtZhong);
	updateCahe(CaheJiu,txtJiu);
	
	return true;
}
void GameStoreLayer::menuCallBack(Ref* sender,TouchEventType type)
{
	if(type != TouchEventType::TOUCH_EVENT_BEGAN)
		return;
	int tag = ((Button*)sender)->getTag();
	switch (tag)
	{
	case GAME_BTN_BUYZHOGN:
		updateTextFiled(CaheZhong,ZHONG_PRICE,txtZhong);
		break;
	case GAME_BTN_FANG:
		updateTextFiled(CaheBao,BAO_PRICE,txtBao);
		break;
	case GAME_BTN_JIU:
		updateTextFiled(CaheJiu,JIU_PRICE,txtJiu);
		break;
	case GAME_BTN_REBACK:
		setRebackState(true);
		this->getParent()->resume();
		//this->getParent()->schedule(SEL_SCHEDULE(&InGameLayer::gameStep),0.02f);
		//this->getParent()->resumeSchedulerAndActions();
	 	//Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(),true);
		this->removeFromParent();
		break;
	case GAME_BTN_MORE:
		break;
	}
}
void GameStoreLayer::updateCahe(int Cahe,cocos2d::ui::TextAtlas* ttf)
{
	char chCahe[10];
	sprintf(chCahe,"%d",Cahe);
	ttf->setStringValue(chCahe);
}
void GameStoreLayer::updateTextFiled(int& data,int cost ,cocos2d::ui::TextAtlas* ttf)
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
	UserDefault::getInstance()->setIntegerForKey("bamboo",Cahezhu);
	UserDefault::getInstance()->setIntegerForKey("zhong",CaheZhong);
	UserDefault::getInstance()->setIntegerForKey("jiu",CaheJiu);
	UserDefault::getInstance()->setIntegerForKey("DefensiveCover",CaheBao);
}
void GameStoreLayer::setRebackState(bool bl)
{
	this->reBack = bl;
}
bool GameStoreLayer::getReBackState()const
{
	return reBack;
}
