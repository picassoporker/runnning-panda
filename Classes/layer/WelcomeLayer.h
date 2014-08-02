#ifndef _WELCOME_LAYER_H_
#define _WELCOME_LAYER_H_
#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
#include "layer/BackGroundLayer.h"

enum WELCOME_BTN
{
	BTN_START = 2000,
	BTN_OPTION,
	BTN_RANK,
	BTN_HELP,
	BTN_STORE
};
class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	CREATE_FUNC(WelcomeLayer);

public:

	static cocos2d::Scene* createScene();

public:

	void menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type);
	void gameStep(float dt);
	void createGameXml();

private:

	BackGroundLayer* mBackground;
};

#endif //_WELCOME_LAYER_H_
