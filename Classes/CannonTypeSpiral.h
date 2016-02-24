#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSpiral : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeSpiral);

	void setExtraState(bool on);

private:
	
	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _inner;
	cocos2d::Sprite* _outter;


};



