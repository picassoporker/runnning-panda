#include "Panda.h"
#include "VisibleRect.h"
#include "Plantform.h"
using namespace cocostudio;
USING_NS_CC;
Panda::Panda(void) : state(PANDA_STATE_IDLE),
								vx(0),
								jumpVy(20),
								flyFlotageVy(0.5f),
								skin(nullptr),
								effect(nullptr),
								gravity(0.98f),
								MIN_VX(17.0f),
								MAX_VX(24),
								MIN_VY(-13.0f),
								MAX_VY(16.5f),
								curPointY(0),
								isUpdataAction(false),
								shouldRun(true)
{
}


Panda::~Panda(void)
{
}
bool Panda::init()
{
	Sprite::init();
	skin = Armature::create("PandaAnimation");
	this->addChild(skin);
	skin->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	skin->getAnimation()->play("run");
	this->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	skin->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(Panda::resetRunAction,this));

	effect = Armature::create("pandaEffectAnimation");
	this->addChild(effect);
	effect->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	effect->setVisible(false);
	effect->getAnimation()->gotoAndPause(10);

	setState(PANDA_STATE_RUN);
	curPointY	=	this->getPositionY();

	return true;
}
void Panda::jump()
{
	state++;
	setState(state);
}
void Panda::setState(int state)
{
	this->state = state;
	switch (state)
	{
	case PANDA_STATE_IDLE:
		gravity					= 0;
		flyFlotageVy			= 0;
		jumpVy					= 0;
		vx							= 0;
		break;
	case PANDA_STATE_RUN:
		if (jumpVy <= -13 && shouldRun)
		{
			shouldRun = false;
			skin->getAnimation()->play("downRoll");
		}else
		{
			shouldRun = true;
			skin->getAnimation()->play("run");
		}
		gravity					= 0;
		flyFlotageVy			= 0;
		jumpVy					= 0;
		vx							= MIN_VX;
		break;
	case PANDA_STATE_JUMP:
		gravity					= 0.98f;
		flyFlotageVy			= 0;
		jumpVy					= MAX_VY;
		vx							= MIN_VX;
		skin->getAnimation()->play("jumpOne");
		break;
	case PANDA_STATE_DOUBLE:
		gravity					= 0.98f;
		flyFlotageVy			= 0;
		jumpVy					= MAX_VY;
		vx							= MIN_VX;
		skin->getAnimation()->play("jumpTwo");
		break;
	case PADNA_STATE_FLY:
		gravity					= 0;
		flyFlotageVy			= 0.3f;
		jumpVy					= 0;
		vx							= 17.0f;
		skin->getAnimation()->play("fly");
		break;
	case PANDA_STATE_DOWN:
		gravity					= 0.98f;
		flyFlotageVy			= 0;
		jumpVy					= 0;
		vx							= MIN_VX;
		skin->getAnimation()->play("jumpOne");
		break;
	}
}
int Panda::getState()const
{
	return state;
}
void Panda::move()
{
	float x = this->getPositionX() + vx < VisibleRect::getVisibleRect().getMaxX() / 4 ? this->getPositionX() + vx :
				VisibleRect::getVisibleRect().getMaxX() / 4;
	float y = this->getPositionY() + jumpVy < VisibleRect::getVisibleRect().getMaxY()  / 2  ? this->getPositionY() + jumpVy:
				VisibleRect::getVisibleRect().getMaxY() / 2 ;
	if (curPointY < VisibleRect::getVisibleRect().getMaxY() / 2  && !isUpdataAction)
		this->setPosition(x,y);
	jumpVy	-= gravity;
	jumpVy += flyFlotageVy;
	curPointY += jumpVy;
	if (jumpVy > MAX_VY)
	{
		jumpVy = MAX_VY ;
	}else if (jumpVy < MIN_VY)
	{
		jumpVy = MIN_VY;
	}
}
int Panda::getCurPointY()const
{
	return curPointY;
}
bool Panda::hitWtihRect(const cocos2d::Rect& targetRect)
{
	return targetRect.containsPoint(this->getPosition());
}
void Panda::setJumpVy(float jump)
{
	this->jumpVy = jump;
}
float Panda::getJumpVy()const
{
	return jumpVy;
}
void  Panda::hitAction()
{
	isUpdataAction	=	true;
	auto moveDown = MoveBy::create(0.05f,Point(0,-20));
	auto moveUp		=	MoveBy::create(0.05f,Point(0,20));
	auto actCallBack= CallFunc::create([&]()
	{
		isUpdataAction		= false;
	});
	auto seq			=	Sequence::create(moveDown,moveUp,actCallBack,nullptr);
	this->runAction(seq);
}
void Panda::setVx(bool maxVx)
{
	if (maxVx)
	{
		this->vx = MAX_VX;
	}else
		this->vx = MIN_VX;
}
float Panda::getVx()const 
{
	if (this->getPositionX() >= VisibleRect::getVisibleRect().getMaxX() / 4)
	{
		return vx;
	}else 
		return 0;
}
void Panda::resetRunAction(cocostudio::Armature* art,cocostudio::MovementEventType type ,const std::string& id)
{
	if (type == MovementEventType::COMPLETE && id == "downRoll")
	{
		skin->getAnimation()->play("run");
	}
}
void Panda::playEffect(PANDA_EFFECT effectType)
{
	effect->setVisible(true);
	switch (effectType)
	{
	case PANDA_EFFECT_SPEED:
		effect->getAnimation()->play("speed");
		break;
	case PANDA_EFFECT_EAT:
		effect->getAnimation()->play("eat");
		break;
	}
}
void Panda::stopPandaArm()
{
	skin->pause();
}
void Panda::playPandaArm()
{
	skin->resume();
}