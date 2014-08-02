#ifndef _GAMEOVER_LAYER_H_
#define _GAMEOVER_LAYER_H_
#include "cocos/ui/CocosGUI.h"
#include "cocos2d.h"
enum OVER_BTN
{
	BTN_REBACK = 200,
	BTN_TOSTORE
};
class GameOverLayer :  public cocos2d::Layer
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	virtual bool init();
	CREATE_FUNC(GameOverLayer);

	static cocos2d::Scene* createScene();

private:;
	void menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type);
	void runStore(float dt);
	void showTxt(float dt);
	void updateTextFiled(int num,cocos2d::ui::TextAtlas* ttf);
	void GameOverLayer::assetsLoaded(float dt);
private:
	cocos2d::ui::TextAtlas* txtDist;
	cocos2d::ui::TextAtlas* txtBestScore;
	cocos2d::ui::TextAtlas* txtScore;
	cocos2d::LabelTTF* txt;
	int score;
	int count;
	int bestScore;
	int tenNum;
	int BaiNum;
};

#endif // !_GAMEOVER_LAYER_H_
