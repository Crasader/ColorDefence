#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeLargeWave : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeLargeWave);


private:
	
	void attackOnce();

	cocos2d::Sprite* _rot;

	void setDirection();

};



