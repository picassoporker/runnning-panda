#ifndef _FOOD_H_
#define  _FOOD_H_
#include "cocos2d.h"
enum FOOD_TYPE
{
	FOOD_TYPE_BAO,
	FOOD_TYPE_FOOD,
	FOOD_TYPE_JIU,
	FOOD_TYPE_ZHONG
};
class Food : public cocos2d::Sprite
{
public:
	Food(void);
	~Food(void);
	CREATE_FUNC(Food);

public:
	void move(float vx);
	void setType(int type);
	int getType()const;
	bool hitTest(const cocos2d::Point& hitPoint);
	void reset();
private:
	int type;

};

#endif // !_FOOD_H_
