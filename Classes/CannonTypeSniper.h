#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSniper : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeSniper);

	void tryGetTarget();

private:
	
	void attackOnce();

	//cocos2d::Point originalPosition;
	//bool hasMoved;

	void setDirection();

	cocos2d::Sprite* _barrel;
	cocos2d::Sprite* _barrelColor;


	void pause();
	void resume();

	void setColorInfo(cocos2d::Color3B c3b);


};



