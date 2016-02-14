#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeSniper : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeSniper);

	void tryGetTarget();

private:
	
	void attackOnce();

	//cocos2d::Point originalPosition;
	//bool hasMoved;

	void setDirection();

	cocos2d::Sprite* _barrel;


	void pause();
	void resume();


};



