#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBreaker : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeBreaker);


private:
	
	void attackOnce();

	cocos2d::Sprite* _readyBullet;
	cocos2d::Sprite* _handle;

	void pause();

	void resume();

	void setDirection();

};



