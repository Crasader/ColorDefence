#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeRage : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeRage);

	void tryGetTarget();

private:
	
	void attackOnce();

	int _attackIntervalWhenRage;

	bool _rage;
	int _countForRage;

	void update(float delta);

	void setRage(bool rage);

	void setDirection();

};



