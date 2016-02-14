#pragma once

#include "Bullet.h"


class BulletTypeBounce : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeBounce);

	

	void setDamage(float damage , float bounceRange, float damageReduceFactor, int bounceTimes );

	void setTarget(Enemy* enemy);

protected:

	cocos2d::Vector<Enemy*> targetsBouncedOver;
	cocos2d::ParticleSystem* _snow;

	float _bounceRange;
	float _damageReduceFactor;
	int _bounceTimes;

	void bounce();

	virtual void explode();

	void update(float delta);

};

