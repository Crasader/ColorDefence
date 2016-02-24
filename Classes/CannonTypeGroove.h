#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeGroove : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeGroove);


private:
	
	void attackOnce();

	cocos2d::Sprite* _outter[12];

	void setDirection();


	int _r_timer;



};



