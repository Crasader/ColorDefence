#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSpreadOnBoss : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeSpreadOnBoss);


private:
	
	void attackOnce();

	void tryGetTarget();

	cocos2d::Sprite* _core;

	void setDirection();

	void update(float delta);

};



