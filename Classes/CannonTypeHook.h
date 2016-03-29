#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeHook : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeHook);

	Enemy* getCatchingTarget();

	void catchOnce(bool catching,  cocos2d::Point targetPosition);

private:

	void attackOnce();

	cocos2d::Sprite* _readyBullet;
	cocos2d::Sprite* _handle;
	cocos2d::Node* _center;

	void pause();

	void resume();

	void setDirection();

	

};



