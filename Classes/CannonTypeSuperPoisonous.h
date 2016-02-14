#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSuperPoisonous : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeSuperPoisonous);

	void setColorInfo(cocos2d::Color3B c3b);


	void pause();
	void resume();

private:
	
	void attackOnce();

	cocos2d::Sprite* _cover;

	void setDirection();
};



