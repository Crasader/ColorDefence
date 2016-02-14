#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeProducer : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeProducer);

	

private:

	void attackOnce();

	cocos2d::Sprite* _gear[2];
	
	void setDirection();

	int _attackCounter;

};



