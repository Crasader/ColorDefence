#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeProducer : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeProducer);

	

private:

	void attackOnce();

	cocos2d::Sprite* _gear[2];
	
	void setDirection();

	int _attackCounter;

};



