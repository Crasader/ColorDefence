#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypePoisonousMulti : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypePoisonousMulti);


private:
	
	void attackOnce();

	bool _canRotate;


	void setDirection();

};



