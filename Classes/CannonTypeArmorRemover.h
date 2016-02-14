#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeArmorRemover : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeArmorRemover);


private:
	
	void attackOnce();

	void setDirection();

	cocos2d::Sprite* _cover;

};



