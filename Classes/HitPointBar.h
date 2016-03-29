#pragma once

#include "cocos2d.h"


class HitPointBar : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(HitPointBar);

	void setHitPoint(float hpRate);

private:


	cocos2d::Sprite* _hpSprite;
	cocos2d::ProgressTimer* _hpBar;
};

