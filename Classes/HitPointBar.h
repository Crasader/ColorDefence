#pragma once

#include "cocos2d.h"


class HitPointBar : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(HitPointBar);

	void setHitPoint(float hpRate);

private:


	cocos2d::Sprite* _hpSprite;
	cocos2d::ProgressTimer* _hpBar;
};

