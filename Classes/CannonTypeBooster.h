#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBooster : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeBooster);

	void tryGetTarget();

private:

	void attackOnce();

	void update(float delta);

	Cannon* _targetCannon;

	void setDirection();
};



