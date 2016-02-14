#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeArmorRemover : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeArmorRemover);


private:
	
	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _cover;

};



