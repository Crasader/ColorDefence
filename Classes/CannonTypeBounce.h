#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBounce : public Cannon
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(CannonTypeBounce);

	void pause();
	void resume();

private:
	
	void attackOnce();

	float _bounceRange;
	float _damageReduceFactor;
	int _bounceTimes;

	cocos2d::Sprite*  _gate;
	cocos2d::ParticleSystem* _snow;

};



