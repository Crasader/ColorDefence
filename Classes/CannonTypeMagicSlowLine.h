#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMagicSlowLine : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeMagicSlowLine);

	void tryGetTarget();

private:
	
	void attackOnce();

	

};



