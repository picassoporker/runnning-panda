#include "Plantform.h"
#include "VisibleRect.h"
USING_NS_CC;

Plantform::Plantform(void) : next(nullptr),
										 pre(nullptr),
										 width(0),
										 height(18)
{
}

Plantform::~Plantform(void)
{

}
void Plantform::setPlantform()
{
	auto head = Sprite::createWithSpriteFrameName("setp_1.png");
	this->addChild(head);
	head->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	float nextX = 0;
	nextX  = head->getPositionX() + head->getContentSize().width;
	int randomStep = CCRANDOM_0_1() * 3 + 2;
	int randomNum = CCRANDOM_0_1() * 8 + 3; 
	char chStep[256];
	Sprite* next = nullptr;
	while (--randomNum)
	{
		sprintf(chStep,"setp_%d.png",randomStep);
		next = Sprite::createWithSpriteFrameName(chStep);
		this->addChild(next);
		next->setPositionX(nextX);
		next->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		nextX	=	next->getPositionX() + next->getContentSize().width;
	}
	auto back = Sprite::createWithSpriteFrameName("setp_5.png");
	this->addChild(back);
	back->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	back->setPositionX(nextX);
	width = back->getPositionX() + back->getContentSize().width;
}
Plantform* Plantform::first = nullptr;
void Plantform::initPlantfromList(int num, cocos2d::Node* parent)
{
	
	first = Plantform::create();
	first->setPlantform();
	parent->addChild(first);
	first->setPosition(0,150);
	first->setAnchorPoint(Point::ZERO);

	Plantform* cur = first;
	float nextX		  = 0;
	float nextY		  = 0;
	while (--num)
	{
		cur->next = Plantform::create();
		cur->next->setPlantform();
		cur->next->pre	=	cur;
		cur = cur->next;
		parent->addChild(cur);
		cur->setAnchorPoint(Point::ZERO);
		nextX  = cur->pre->getPositionX() + cur->pre->width + CCRANDOM_0_1() * 400 + 100;
		nextY = cur->pre->getPositionY()  + CCRANDOM_0_1() * 300 -150 < 0 ? 100 : cur->pre->getPositionY()  + CCRANDOM_0_1() * 300 -150;
	
		cur->setPosition(nextX,nextY);
	}
	cur->next = first;
	first->pre = cur;
}
const cocos2d::Rect& Plantform::getHitRect(cocos2d::Node* global)const
{
	float x = this->getPositionX();
	float y = this->getPositionY();
	if (global)
	{
		Point g = global->convertToWorldSpace(this->getPosition());
		x = g.x;
		y = g.y;
	}
	hitRect = Rect(x,y,width,height);
	return hitRect;
}
void Plantform::move(float vx)
{
	float x = this->getPositionX() - vx;
	float y = this->getPositionY() ;
	this->setPositionX(x);
	if (x <= -width)
	{
		x = pre->getPositionX() + pre->width + 100 + CCRANDOM_0_1() * 590;
		y = pre->getPositionY() + CCRANDOM_0_1() * 200 - 100 < 150 ? 
			100 : pre->getPositionY() + CCRANDOM_0_1() * 200 - 100;

		if (y >= VisibleRect::top().y * 2 / 3 )
		{
			y = VisibleRect::top().y / 2 + 50;
		}else if (y <= 20)
		{
			y = 100;
		}

		this->setPosition(x,y);
	}
}

Plantform* Plantform::getNext()const
{
	return next;
}
void Plantform::hitAction(const cocos2d::Point& targetPoint)
{
	Point worldPoint = this->getParent()->convertToWorldSpace(this->getPosition());
	Point dPoint		=	targetPoint - worldPoint;
	auto moveDown = MoveBy::create(0.05f,Point(0,-(20 - dPoint.y)));
	auto moveUp		= MoveBy::create(0.05f,Point(0,18));
	auto seq			=	Sequence::create(moveDown,moveUp,nullptr);
	this->runAction(seq);
}