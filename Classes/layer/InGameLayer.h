#ifndef _INGAME_LAYER_H_
#define  _INGAME_LAYER_H_
#include "cocos2d.h"
#include "BackGroundLayer.h"
#include "object\Plantform.h"
#include "object\Panda.h"
#include "object\Food.h"
#include "pools\FoolPool.h"
#include "layer\GameStoreLayer.h"

enum GAME_BTN
{
	GAME_BTN_PAUSEGAME = 1,
	GAME_BTN_JUMP,
	GAME_BTN_FIRE
};
class InGameLayer: public cocos2d::Layer
{
public:
	InGameLayer(void);
	~InGameLayer(void);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	CREATE_FUNC(InGameLayer);

public:
	static cocos2d::Scene* createScene();
	void gameStep(float dt);
private:
	
	void moveAllElenment();
	void followView();
	void hitTest();
	bool checkInRect(float x ,const cocos2d::Rect& r);
	void createFood();
	void moveAllFood();
	void hitFoodTest();
	void menuCallBack(cocos2d::Ref* sender ,cocos2d::ui::TouchEventType type);
	void setItemState(bool bl);
	void removeItem();
	void updateTextFiled(int num,cocos2d::ui::TextAtlas* ttf);
	void readGameData(const char* fileName);
	void gameOver();
private:
	BackGroundLayer* mBackground;
	cocos2d::Layer* elementLayer;
	GameStoreLayer* storeLayer;
	Panda* mPanda;
	float createFoodGap;
	float jiuPower;
	cocos2d::Vector<Food*>foodList;
	FoolPool mFoodPool;
	bool isInStoreLayer;
	cocos2d::MenuItemSprite* item;
	int curDistCount;
	//µÀ¾ß
	int zhu;
	int bao;
	int jiu;
	int zhong;
	int score;
	cocos2d::ui::TextAtlas* txtFarAwayCount;
	cocos2d::ui::TextAtlas* txtJiuCount;
	cocos2d::ui::TextAtlas* txtFangCount;
	cocos2d::ui::TextAtlas* txtZhongCount;
	cocos2d::ui::TextAtlas* txtBambooCount;
};
inline bool InGameLayer::checkInRect(float x ,const cocos2d::Rect& r)
{
	return x > r.getMinX() && x < r.getMaxX();
}
#endif // !_INGAME_LAYER_H_
