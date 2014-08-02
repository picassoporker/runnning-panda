#include "VisibleRect.h"
#include "Food.h"
USING_NS_CC;

Food::Food(void) : type(0)
{
}


Food::~Food(void)
{
}
void Food::setType(int type)
{
	char* foodTypeList[] = 
	{
		"bao.png",
		"food.png",
		"jiu.png",
		"zhong.png"
	};
	this->type = type;
	initWithSpriteFrameName(foodTypeList[type]);
}

void Food::move(float vx)
{
	this->setPosition(this->getPosition() - Point(vx,0));
}

int Food::getType()const
{
	return type;
}
bool Food::hitTest(const cocos2d::Point& hitPoint)
{
	float dx = hitPoint.x - this->getPositionX();
	float dy = hitPoint.y - this->getPositionY();
	float dist = sqrt(dx * dx + dy * dy);
	if (dist < 79 / 2 + this->getContentSize().width / 2)
	{
		return true;
	}
	return false;
}
void Food::reset()
{
	this->removeFromParent();
	this->setPositionX(VisibleRect::right().x + 100);
}