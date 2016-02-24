#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeExplodeOnDeath : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeExplodeOnDeath);


private:
	
	void attackOnce();



};



