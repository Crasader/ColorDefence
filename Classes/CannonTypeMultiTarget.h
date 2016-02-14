#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMultiTarget : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeMultiTarget);


private:
	
	void tryGetTarget();
	
	void attackOnce();

	void setDirection();

	void setExtraState(bool on);



};



