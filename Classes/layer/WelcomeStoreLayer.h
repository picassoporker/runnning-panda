#ifndef _WELCOMESTORE_LAYER_H_
#define _WELCOMESTORE_LAYER_H_

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

enum STORE_BUTTON_TAG
{
	BUTTON_TAG_JIU,
	BUTTON_TAG_ZHONG,
	BUTTON_TAG_BAO, //ΪFANG
	BUTTON_TAG_REBACK
};
class WelcomeStoreLayer : public cocos2d::Layer
{
public:
	WelcomeStoreLayer(void);
	~WelcomeStoreLayer(void);
public:
	virtual bool init();
	CREATE_FUNC(WelcomeStoreLayer);
public:
	static cocos2d::Scene* createScene();

private:
	void updateCahe(int Cahe,cocos2d::ui::TextAtlas* ttf);
	void updateTextFiled(int& data,int cost ,cocos2d::ui::TextAtlas* ttf);
	void menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type);
	void readXml();
private:
	cocos2d::ui::Button* btnBuyZhong;
	cocos2d::ui::Button* btnBuyFang;
	cocos2d::ui::Button* btnBuyJiu;
	cocos2d::ui::Button* btnReback;
	cocos2d::ui::TextAtlas* txtJiu;
	cocos2d::ui::TextAtlas* txtZhong;
	cocos2d::ui::TextAtlas* txtZhu;
	cocos2d::ui::TextAtlas* txtBao;
	const int JIU_PRICE;
	const int ZHONG_PRICE;
	const int BAO_PRICE;
	int CaheBao;
	int CaheZhong;
	int CaheJiu;
	int Cahezhu;
};

#endif // !_WELCOMESTORE_LAYER_H_
