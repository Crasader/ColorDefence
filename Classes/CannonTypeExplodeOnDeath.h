#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeExplodeOnDeath : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeExplodeOnDeath);


private:
	
	void attackOnce();



};



