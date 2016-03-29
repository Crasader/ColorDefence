#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeDuplicate : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeDuplicate);

	void setColorInfo(cocos2d::Color3B c3b);


	void duplicateAtPoint(cocos2d::Point point);

private:
	
	void attackOnce();



};



