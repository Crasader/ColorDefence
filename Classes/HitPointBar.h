#pragma once

#include "cocos2d.h"


class HitPointBar : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(HitPointBar);

	void setHitPoint(float hpRate);

private:


	cocos2d::Sprite* _hpSprite;
	cocos2d::ProgressTimer* _hpBar;
};

