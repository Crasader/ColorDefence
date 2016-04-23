#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSpiral : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeSpiral);

	void setExtraState(bool on);

	void pause();
	void resume();

private:
	
	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _inner;
	cocos2d::Sprite* _outter;


};



