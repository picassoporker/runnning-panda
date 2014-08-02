#ifndef _GAMESTORE_LAYER_H_
#define _GAMESTORE_LAYER_H_
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
enum STORE
{
	GAME_BTN_BUYZHOGN = 200,
	GAME_BTN_FANG,
	GAME_BTN_JIU,
	GAME_BTN_REBACK,
	GAME_BTN_MORE
};
class GameStoreLayer : public cocos2d::Layer
{
public:
	GameStoreLayer(void);
	~GameStoreLayer(void);

	virtual bool init();
	CREATE_FUNC(GameStoreLayer);
private:

	void menuCallBack(cocos2d::Ref* sender,cocos2d::ui::TouchEventType type);
	void updateCahe(int Cahe,cocos2d::ui::TextAtlas* ttf);
	void updateTextFiled(int& data,int cost ,cocos2d::ui::TextAtlas* ttf);
public:
	void setRebackState(bool bl);
	bool getReBackState()const;
	
private:
	cocos2d::ClippingNode* clip;
	cocos2d::Size  winSize;
	bool reBack;
	cocos2d::ui::TextAtlas* txtJiu;
	cocos2d::ui::TextAtlas* txtZhong;
	cocos2d::ui::TextAtlas* txtBao;
	const int JIU_PRICE;
	const int ZHONG_PRICE;
	const int BAO_PRICE;
	int CaheBao;
	int CaheZhong;
	int CaheJiu;
	int Cahezhu;
};

#endif // !_GAMESTORE_LAYER_H_
