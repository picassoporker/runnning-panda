#ifndef _PANDA_H_
#define _PANDA_H_
#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
enum PANDA_STATE
{
	PANDA_STATE_IDLE = 2000,
	PANDA_STATE_RUN,
	PANDA_STATE_JUMP,
	PANDA_STATE_DOUBLE,
	PADNA_STATE_FLY,
	PANDA_STATE_DOWN
};
enum PANDA_EFFECT
{
	PANDA_EFFECT_SPEED,
	PANDA_EFFECT_EAT
};
class Panda : public cocos2d::Sprite
{
public:
	Panda(void);
	~Panda(void);
	virtual bool init();
	CREATE_FUNC(Panda);

public:
	void jump();
	void setState(int state);
	int getState()const;
	void move();
	int getCurPointY()const;
	bool hitWtihRect(const cocos2d::Rect& targetRect);
	void setJumpVy(float jump);
	float getJumpVy()const;
	void hitAction();
	void setVx(bool maxVx);
	float getVx()const ;
	void resetRunAction(cocostudio::Armature* art,cocostudio::MovementEventType type ,const std::string& id);
	void playEffect(PANDA_EFFECT effectType);
	void stopPandaArm();
	void playPandaArm();
private:
	int state;
	float vx;
	float gravity;
	float jumpVy;
	float flyFlotageVy;
	float curPointY;
	const int MAX_VX;
	const int MIN_VX;
	const int MAX_VY;
	const int MIN_VY;
	cocostudio::Armature* skin;
	cocostudio::Armature* effect;
	bool isUpdataAction;
	bool shouldRun;
};

#endif // !_PANDA_H_
