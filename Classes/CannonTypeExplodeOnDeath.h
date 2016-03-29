#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeExplodeOnDeath : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeExplodeOnDeath);


private:
	
	void attackOnce();



};



