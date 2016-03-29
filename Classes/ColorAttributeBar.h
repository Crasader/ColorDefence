#pragma once

#include "cocos2d.h"


class ColorAttributeBar : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
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

