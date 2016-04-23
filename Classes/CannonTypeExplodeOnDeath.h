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

	void pause();
	void resume();


	void setColorInfo(cocos2d::Color3B c3b);

private:
	
	void attackOnce();

	cocos2d::ParticleSystem* _particle;
	cocos2d::Sprite* _head;



};



