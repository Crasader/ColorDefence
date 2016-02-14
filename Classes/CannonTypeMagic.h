#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMagic : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeMagic);

	void tryGetTarget();

private:
	
	void attackOnce();

	cocos2d::Sprite* _core;
	void setDirection();
	bool fading;

	void update(float delta);

};



