#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeChains : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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



