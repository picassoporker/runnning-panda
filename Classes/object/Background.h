#ifndef _Background_H_
#define _Background_H_
#include "cocos2d.h"
class Background : public cocos2d::Sprite
{
public:
	Background(void);
	~Background(void);
public:
	static Background* create(const std::string& file);
public:
	void move(float vx);
private:
	bool init(const std::string& file);
private:
	cocos2d::Sprite* one;
	cocos2d::Sprite* two;
};

#endif // !_Background_H_
