#include "object\Food.h"
#ifndef _FOODPOOL_H_
#define  _FOODPOOL_H_

class FoolPool
{
public:
	FoolPool(void);
	~FoolPool(void);
public:
	void init();
	void takeIn(Food* food);
	Food* takeOut();
private:
	const int MIN_COUNT;
	const int MAX_COUNT;
	const int REPLENISH;

	cocos2d::Vector<Food*> pool;
};

#endif // !_FOODPOOL_H_
