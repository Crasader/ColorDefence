#pragma once

#include "Bullet.h"


class BulletTypeBounce : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
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

