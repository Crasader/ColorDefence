﻿#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeFlower : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeFlower);


	void setColorInfo(cocos2d::Color3B c3b);


	void tryGetTarget();


	void pause();
	void resume();


private:
	
	cocos2d::Sprite* _petal[5];

	void attackOnce();

	void collaborate();


	void setDirection();

	void bloom();

};



