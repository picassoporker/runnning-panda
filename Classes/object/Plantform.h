#ifndef _PLANTFORM_H_
#define _PLANTFORM_H_
#include "cocos2d.h"
class Plantform : public cocos2d::Sprite
{
public:
	Plantform(void);
	~Plantform(void);
	
	CREATE_FUNC(Plantform);
public:
	static void initPlantfromList(int num, cocos2d::Node* parent);
	static Plantform* first;
private:
	void setPlantform();
public:
	void move(float vx);
	Plantform* getNext()const;
	const cocos2d::Rect& getHitRect(cocos2d::Node* global = nullptr)const;
	void hitAction(const cocos2d::Point& targetPoint);
private:
	Plantform* next ;
	Plantform* pre;
	float width;
	float height;
	mutable cocos2d::Rect hitRect;
};

#endif // !_PLANTFORM_H_
