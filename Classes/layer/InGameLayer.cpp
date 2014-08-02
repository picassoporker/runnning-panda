#include "InGameLayer.h"
#include "VisibleRect.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "GameOverLayer.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
InGameLayer::InGameLayer(void) : mPanda(nullptr),
													elementLayer(nullptr),
													storeLayer(nullptr),
													mBackground(nullptr),
													createFoodGap(30),
													jiuPower(0),
													foodList(),
													isInStoreLayer(false),
													curDistCount(0),
													bao(0),
													zhu(0),
													jiu(0),
													zhong(0),
													score(0)

{
}

InGameLayer::~InGameLayer(void)
{
}

bool InGameLayer::init()
{
	Layer::init();

	Sprite* bg = Sprite::create("background/background.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);

	elementLayer = Layer::create();
	this->addChild(elementLayer);
	elementLayer->setAnchorPoint(Point::ZERO);
	
	mBackground = BackGroundLayer::create();
	elementLayer->addChild(mBackground);
	mBackground->setAnchorPoint(Point::ZERO);

	Plantform::initPlantfromList(5,elementLayer);
	
	mPanda		=	Panda::create();
	this->addChild(mPanda);
	mPanda->setPosition(100,150);

	mFoodPool.init();

	auto uiWidget	=	GUIReader::getInstance()->widgetFromJsonFile("InGameUI/UIInGame.json");
	this->addChild(uiWidget);
	Button* btnPauseGame = (Button*)uiWidget->getChildByName("btnPauseGame");
	Button* btnJump = (Button*)uiWidget->getChildByName("btnJump");
	Button* btnFire = (Button*)uiWidget->getChildByName("btnFire");

	btnPauseGame->addTouchEventListener(this,SEL_TouchEvent(&InGameLayer::menuCallBack));
	btnJump->addTouchEventListener(this,SEL_TouchEvent(&InGameLayer::menuCallBack));
	btnFire->addTouchEventListener(this,SEL_TouchEvent(&InGameLayer::menuCallBack));


	//更新距离文本
	txtFarAwayCount		= (TextAtlas*)uiWidget->getChildByName("txtFarAwayCount");

	txtBambooCount			= (TextAtlas*)uiWidget->getChildByName("txtBambooCount");
	txtZhongCount			= (TextAtlas*)uiWidget->getChildByName("txtZhongCount");
	txtJiuCount				= (TextAtlas*)uiWidget->getChildByName("txtJiuCount");
	txtFangCount				= (TextAtlas*)uiWidget->getChildByName("txtFangCount");
	readGameData("UserDefault.xml");

	return true;

}

void InGameLayer::onEnterTransitionDidFinish()
{
	this->schedule(SEL_SCHEDULE(&InGameLayer::gameStep),0.02f);
	
}

Scene* InGameLayer::createScene()
{
	auto sc = Scene::create();
	auto ly  = InGameLayer::create();
	sc->addChild(ly);
	return sc;
}

void InGameLayer::gameStep(float dt)
{
	moveAllElenment();
	followView();
	hitTest();
	createFood();
	moveAllFood();
	hitFoodTest();
	removeItem();
	curDistCount++;
	updateTextFiled(curDistCount,txtFarAwayCount);
	gameOver();
}
void InGameLayer::removeItem()
{
	if (isInStoreLayer)
	{
		updateTextFiled(zhu,txtBambooCount);
		updateTextFiled(zhong,txtZhongCount);
		updateTextFiled(bao,txtFangCount);
		updateTextFiled(jiu,txtJiuCount);
		item->setContentSize(Size(0,0));
		this->removeChild(item);
		mPanda->playPandaArm();
	}
}
void InGameLayer::moveAllElenment()
{
	mBackground->move(mPanda->getVx());
	Plantform* cur = Plantform::first;
	do 
	{
		cur->move(mPanda->getVx());
		cur = cur->getNext();
	} while (cur != Plantform::first);
	mPanda->move();
	if (jiuPower > 0)
	{
		jiuPower -= 1.5f;
		mPanda->setVx(true);
	}else
	{
		jiuPower = 0;
		mPanda->setVx(false);
	}
}
void InGameLayer::menuCallBack(cocos2d::Ref* sender ,cocos2d::ui::TouchEventType type)
{
		int tag = ((Widget*)sender)->getTag();	

		switch (tag)
		{
		case GAME_BTN_PAUSEGAME:
			if (type != TOUCH_EVENT_ENDED)
			{
				log("GAME_BTN_PAUSEGAME"); 
				this->pause();
				//this->unscheduleAllSelectors();
				mPanda->stopPandaArm();
				//弹出商城界面
				//Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this,true);
				storeLayer	=	GameStoreLayer::create();
				this->addChild(storeLayer,18);
				Size winSize = Director::getInstance()->getVisibleSize();
			    item = MenuItemImage::create();
				item->setContentSize(CCSizeMake(winSize.width, winSize.height));
				Menu* menu = CCMenu::create(item, NULL);
				menu->setTouchEnabled(false);
				this->addChild(menu,17);
				setItemState(true);
			}
			break;
		case GAME_BTN_JUMP:
			log("GAME_BTN_JUMP");
			
			if (mPanda->getState() == PANDA_STATE::PADNA_STATE_FLY && type == TOUCH_EVENT_ENDED)
			{
				mPanda->setState(PANDA_STATE_DOWN);
			}
			else if (type != TOUCH_EVENT_ENDED )
			{
				mPanda->jump();
			}
			break;
		case GAME_BTN_FIRE:
			log("GAME_BTN_FIRE");
			break;
		}
}
void InGameLayer::setItemState(bool bl)
{
	this->isInStoreLayer = bl;
}

void InGameLayer::followView()
{
	float y		 = mPanda->getCurPointY() > VisibleRect::top().y /2 ? mPanda->getCurPointY() : VisibleRect::top().y /2;
	float dist	 = VisibleRect::top().y / 2 - y;
	elementLayer->setPositionY(dist);
}

void InGameLayer::hitTest()
{
	Plantform* cur = Plantform::first;
	bool isDownFormStep = true;
	do 
	{
		if (mPanda->hitWtihRect(cur->getHitRect(elementLayer)) && 
			mPanda->getJumpVy() < 0 && 
			mPanda->getState() !=PANDA_STATE_RUN)
		{
			mPanda->hitAction();
			cur->hitAction(mPanda->getPosition());
			mPanda->setState(PANDA_STATE_RUN);
		}
		if (mPanda->getState() == PANDA_STATE_RUN && 
			checkInRect(mPanda->getBoundingBox().getMinX(),cur->getHitRect(elementLayer)) ||
			checkInRect(mPanda->getBoundingBox().getMaxX(),cur->getHitRect(elementLayer))
			)
		{
			isDownFormStep = false;
		}
		cur =cur->getNext();
	} while (cur != Plantform::first);
	if (isDownFormStep && mPanda->getState() == PANDA_STATE_RUN)
	{
		mPanda->setState(PANDA_STATE_JUMP);
		mPanda->setJumpVy(0);
	}
}
void InGameLayer::createFood()
{
	if (createFoodGap > 0)
	{
		createFoodGap--;
	}else
	{
		auto mFood = mFoodPool.takeOut();
		mFood->setType(CCRANDOM_0_1() * 4);
		elementLayer->addChild(mFood);
		//设置坐标在踏板上面
		float x = VisibleRect::right().x + 100;
		float y = 0;
		Plantform* cur = Plantform::first;
		do 
		{
			if (checkInRect(VisibleRect::right().x ,cur->getHitRect(elementLayer)))
			{
				y = cur->getPositionY() + 100;
				break;
			}
			cur = cur->getNext();
		} while (cur != Plantform::first);
		y = y > 0 ? y : 220;
		mFood->setPosition(x,y);
		foodList.pushBack(mFood);
		createFoodGap = 30;
	}
}
void InGameLayer::moveAllFood()
{
	Food* getFood = nullptr;
	float vx = mPanda->getVx();
	for (int i = foodList.size() - 1; i >= 0 ; i--)
	{
		getFood = foodList.at(i);
		getFood->move(vx);
		if (getFood->getPositionX() <= -getFood->getContentSize().width)
		{
			mFoodPool.takeIn(getFood);
			elementLayer->removeChild(getFood);
			foodList.eraseObject(getFood);
		}
	}
}
void InGameLayer::hitFoodTest()
{
	Food* getFood = nullptr;
	Point foodWorldPoint(0,0);
	float dist = 0;
	float dx = 0;
	float dy = 0;
	for (int i = foodList.size() - 1; i >= 0 ; i--)
	{
		getFood = foodList.at(i);
		foodWorldPoint = getFood->getParent()->convertToWorldSpace(getFood->getPosition());
		dx = mPanda->getPositionX() - foodWorldPoint.x;
		dy = mPanda->getPositionY() - foodWorldPoint.y;
		dist = sqrt(dx * dx + dy * dy );
		if (dist <= 50 + 30)
		{
			if (getFood->getType() == FOOD_TYPE_JIU)
			{
				jiuPower += 150;
				score	+= 50;
				mPanda->playEffect(PANDA_EFFECT::PANDA_EFFECT_SPEED);
			}else if (getFood->getType()	== FOOD_TYPE_FOOD)
			{
				zhu++;
				score	+= 20;
				updateTextFiled(zhu,txtBambooCount);
			}else if (getFood->getType()	== FOOD_TYPE_ZHONG)
			{
				zhong++;
				score	+= 10;
				updateTextFiled(zhong,txtZhongCount);
			}else if (getFood->getType()	== FOOD_TYPE_BAO)
			{
				score	+= 60;
			}
			mFoodPool.takeIn(getFood);
			elementLayer->removeChild(getFood);
			foodList.eraseObject(getFood);
		}
	}
}
void InGameLayer::updateTextFiled(int num,cocos2d::ui::TextAtlas* ttf)
{
	char chTxt[10];
	sprintf(chTxt,"%d",num);
	ttf->setStringValue(chTxt);
}
void InGameLayer::readGameData(const char* fileName)
{
	std::string filePath							= FileUtils::getInstance()->getWritablePath() + fileName;
	tinyxml2::XMLDocument* pDoc		= new tinyxml2::XMLDocument();
	XMLError errorId = pDoc->LoadFile(filePath.c_str());
	if (errorId != 0) {
		//xml格式错误
		return;
	}
	XMLElement* root							=	pDoc->RootElement();
	XMLElement* bamboo					=	root->FirstChildElement();
	updateTextFiled(atoi(bamboo->GetText()),txtBambooCount);
	zhu = atoi(bamboo->GetText());
	XMLElement* hongZhong				=	bamboo->NextSiblingElement();
	updateTextFiled(atoi(hongZhong->GetText()),txtZhongCount);
	zhong = atoi(hongZhong->GetText());
	XMLElement* jiuEle							=	hongZhong->NextSiblingElement();
	updateTextFiled(atoi(jiuEle->GetText()),txtJiuCount);
	jiu	=	atoi(jiuEle->GetText());
	XMLElement* DefensiveCover			=	jiuEle->NextSiblingElement();
	updateTextFiled(atoi(DefensiveCover->GetText()),txtFangCount);
	bao = atoi(DefensiveCover->GetText());
	delete pDoc;
}
void InGameLayer::gameOver()
{
	if (mPanda->getPositionY() <= -50)
	{
		//把游戏的数据写入XML
		UserDefault::getInstance()->setIntegerForKey("bamboo",zhu);
		UserDefault::getInstance()->setIntegerForKey("zhong",zhong);
		UserDefault::getInstance()->setIntegerForKey("jiu",jiu);
		UserDefault::getInstance()->setIntegerForKey("DefensiveCover",bao);
		UserDefault::getInstance()->setIntegerForKey("DistCount",curDistCount);
		UserDefault::getInstance()->setIntegerForKey("curScore",curDistCount * 100 + score);
		this->unschedule(SEL_SCHEDULE(&InGameLayer::gameStep));
		Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f,GameOverLayer::createScene()));
	}
}