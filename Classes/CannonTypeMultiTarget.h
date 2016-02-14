#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMultiTarget : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeMultiTarget);


private:
	
	void tryGetTarget();
	
	void attackOnce();

	void setDirection();

	void setExtraState(bool on);



};



