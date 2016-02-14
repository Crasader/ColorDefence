#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSpreadOnBoss : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeSpreadOnBoss);


private:
	
	void attackOnce();

	void tryGetTarget();

};



