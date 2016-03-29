#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSuperPoisonous : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeSuperPoisonous);

	void setColorInfo(cocos2d::Color3B c3b);


	void pause();
	void resume();

private:
	
	void attackOnce();

	cocos2d::Sprite* _cover;

	void setDirection();
};



