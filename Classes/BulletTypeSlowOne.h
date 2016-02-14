#pragma once

#include "Bullet.h"
#include "Enemy.h"


class BulletTypeSlowOne : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeSlowOne);

	float _slowFactor;
	float _slowTime;

	void setDamage(float damage, float slowFactor , float slowTime);

	void setTarget(Enemy* enemy);

protected:

	

	virtual void explode();

	void update(float delta);


	cocos2d::ParticleSystem* emitter;


};

