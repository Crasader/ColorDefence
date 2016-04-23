#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypePoisonousMulti : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypePoisonousMulti);


private:
	
	void attackOnce();

	bool _canRotate;

	cocos2d::Sprite* _core;

	void setDirection();

	void update(float delta);
};



