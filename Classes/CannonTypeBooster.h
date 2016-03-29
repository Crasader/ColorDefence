#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBooster : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeBooster);

	void tryGetTarget();

private:

	void attackOnce();

	void update(float delta);

	Cannon* _targetCannon;

	void setDirection();
};



