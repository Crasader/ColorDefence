#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypePoisonousOne : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypePoisonousOne);


private:
	
	void attackOnce();



};



