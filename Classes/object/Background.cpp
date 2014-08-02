#include "Background.h"
USING_NS_CC;

Background::Background(void): one(NULL),
												two(NULL)
{
}

Background::~Background(void)
{
}

Background* Background::create(const std::string& file )
{
	auto bg = new Background;
	if (bg && bg->init(file))
	{
		bg->autorelease();
		return bg;
	}
	delete bg;
	bg = NULL;
	return NULL;
}
bool Background::init(const std::string& file)
{
	Sprite::init();
	one = Sprite::create(file);
	this->addChild(one);
	one->setAnchorPoint(Point::ZERO);

	two	=	Sprite::create(file);
	this->addChild(two);
	two->setAnchorPoint(Point::ZERO);
	two->setPositionX(one->getPositionX() + one->getContentSize().width);
	return true;
}
void Background::move(float vx)
{
	float oneX = one->getPositionX() - vx;
	float twoX = two->getPositionX() - vx;
	one->setPositionX(oneX);
	two->setPositionX(twoX);
	if (oneX <= -one->getContentSize().width)
	{
		one->setPositionX(two->getPositionX() + two->getContentSize().width);
	}else if (twoX <= -two->getContentSize().width)
	{
		two->setPositionX(one->getPositionX() + one->getContentSize().width);
	}
}