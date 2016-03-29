#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMagic : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeMagic);

	void tryGetTarget();

private:
	
	void attackOnce();

	cocos2d::Sprite* _core;
	void setDirection();
	bool fading;

	void update(float delta);

};



