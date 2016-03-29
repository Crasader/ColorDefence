#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMultiTarget : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeMultiTarget);


private:
	
	void tryGetTarget();
	
	void attackOnce();

	void setDirection();

	void setExtraState(bool on);



};



