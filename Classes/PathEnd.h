#pragma once

#include "cocos2d.h"

class PathEnd : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(PathEnd);

	void setIODirection(bool wayIn);

private:


};

