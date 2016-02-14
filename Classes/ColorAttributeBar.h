#pragma once

#include "cocos2d.h"


class ColorAttributeBar : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(ColorAttributeBar);

	void setAttribute(float max,float min);
	void setGlobalMax(float globalMax);
	
	void setBarColor(cocos2d::Color3B c3b);

private:

	float _globalMax;
	float _max;
	float _min;

	cocos2d::Sprite* _bar_max;
	cocos2d::Sprite* _bar_min;



};

