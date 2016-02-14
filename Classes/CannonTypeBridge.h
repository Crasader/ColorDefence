#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBridge : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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



