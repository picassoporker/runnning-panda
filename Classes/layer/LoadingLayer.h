#ifndef _LOADING_LAYER_H_
#define _LOADING_LAYER_H_
#include "cocos2d.h"
class LoadingLayer : public cocos2d::Layer
{
public:
	LoadingLayer(void);
	~LoadingLayer(void);
	virtual bool init();
	CREATE_FUNC(LoadingLayer);

public:
	static cocos2d::Scene* createScene();

private:
	void assetsLoaded(float dt);
	void armatureLoaded(float dt);
	void textureLoaded(cocos2d::Texture2D* ttu2D);
private:
	int totalResCount;
	int curResLoaded;
	float percentage;
	char chPer[116];
	cocos2d::LabelTTF * ttfPer;	
	//½ø¶ÈÌõ
	cocos2d::ProgressTimer *mProgress;
};

#endif // !_LOADING_LAYER_H_
