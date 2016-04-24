#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeLargeWave : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeLargeWave);

	void tryGetTarget();

private:
	
	void attackOnce();

	cocos2d::Sprite* _rot;

	void setDirection();


};



