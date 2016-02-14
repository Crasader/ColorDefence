#pragma once

#include "cocos2d.h"

class PathEnd : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(PathEnd);

	void setIODirection(bool wayIn);

private:


};

