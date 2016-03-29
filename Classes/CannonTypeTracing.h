#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeTracing : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeTracing);

	void pause();
	void resume();

	void setColorInfo(cocos2d::Color3B c3b);

private:
	
	void attackOnce();


	cocos2d::Sprite*  _gate;
	cocos2d::Sprite*  _gateColor;


	void setDirection();

};



