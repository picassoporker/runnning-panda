#include "BackGroundLayer.h"
USING_NS_CC;

BackGroundLayer::BackGroundLayer(void) : farHill(nullptr),
	nearHill(nullptr),
	farTree(nullptr),
	nearTree(nullptr)
{
}


BackGroundLayer::~BackGroundLayer(void)
{
}
bool BackGroundLayer::init()
{
	Layer::init();
	farHill = Background::create("background/hillViewFar.png");
	this->addChild(farHill);
	farHill->setAnchorPoint(Point::ZERO);
	farHill->setPositionY(150);

	nearHill= Background::create("background/hillViewNear.png");
	this->addChild(nearHill);
	nearHill->setAnchorPoint(Point::ZERO);
	nearHill->setPositionY(50);

	farTree= Background::create("background/treeViewFar.png");
	this->addChild(farTree);
	farTree->setAnchorPoint(Point::ZERO);
	farTree->setPositionY(0);

	nearTree= Background::create("background/treeViewNear.png");
	this->addChild(nearTree);
	nearTree->setAnchorPoint(Point::ZERO);
	nearTree->setPositionY(-50);
	return true;
}
void BackGroundLayer::move(float vx)
{
	farHill->move(vx * 0.2f);
	nearHill->move(vx * 0.4f);
	farTree->move(vx * 0.6f);
	nearTree->move(vx * 0.8f);
}