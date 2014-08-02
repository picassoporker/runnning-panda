#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_
#include "cocos2d.h"
#include "object/Background.h"
class BackGroundLayer : public cocos2d::Layer
{

public:
	BackGroundLayer(void);
	~BackGroundLayer(void);

	virtual bool init();
	CREATE_FUNC(BackGroundLayer);

public:
	void move(float vx);

private:
	Background* farHill;
	Background* nearHill;
	Background* farTree;
	Background* nearTree;
};

#endif // !_BACKGROUND_LAYER_H_
