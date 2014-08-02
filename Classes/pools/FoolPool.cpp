#include "FoolPool.h"


FoolPool::FoolPool(void) :  MIN_COUNT(100),
										MAX_COUNT(200),
										REPLENISH(10),
										pool()
{
}


FoolPool::~FoolPool(void)
{
}
void FoolPool::init()
{
	Food* mFood = nullptr;
	for (int i = 0; i < MIN_COUNT; i++)
	{
		mFood	= Food::create();
		pool.pushBack(mFood);
	}
}
void FoolPool::takeIn(Food* food)
{
	if (pool.size() < MAX_COUNT)
	{
		pool.pushBack(food);
		food->release();
	}
}
Food* FoolPool::takeOut()
{
	if (pool.size() == 0)
	{
		for (int i = 0; i < REPLENISH; i++)
		{
			pool.pushBack(Food::create());
		}
	}
	Food* getFood = pool.at(pool.size() - 1);
	getFood->retain();
	pool.eraseObject(getFood);
	return getFood;
}