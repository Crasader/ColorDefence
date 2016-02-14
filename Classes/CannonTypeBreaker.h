#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBreaker : public Cannon
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(CannonTypeBreaker);


private:
	
	void attackOnce();

	cocos2d::Sprite* _readyBullet;
	cocos2d::Sprite* _handle;

	void pause();

	void resume();

	void setDirection();

};



