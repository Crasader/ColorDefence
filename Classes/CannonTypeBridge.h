#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBridge : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeBridge);

	void tryGetTarget();
	bool tryGetTargetCannon();

	virtual bool getAttackingState();

private:

	void attackOnce();

	void update(float delta);

	Cannon* _targetCannon;

	void setDirection();

	bool _attackingCannon;
};



