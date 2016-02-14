#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeMagic : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeMagic);

	void tryGetTarget();

private:
	
	void attackOnce();

	cocos2d::Sprite* _core;
	void setDirection();
	bool fading;

	void update(float delta);

};



