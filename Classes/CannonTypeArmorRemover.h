#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeArmorRemover : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeArmorRemover);


private:
	
	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _cover;

};



