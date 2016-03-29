#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeChains : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(CannonTypeChains);


	void tryGetTarget();
	
	
	void pause();
	void resume(); 


private:
	
	float _stunTime;

	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _catchers[6];




};



