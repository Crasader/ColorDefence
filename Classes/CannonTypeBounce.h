#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Cannon.h"

class CannonTypeBounce : public Cannon
{
public:

	//初始化
	virtual bool init();  

	//create函数
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



