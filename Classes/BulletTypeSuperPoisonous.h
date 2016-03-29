#pragma once

#include "Bullet.h"


class BulletTypeSuperPoisonous : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeSuperPoisonous);

	float _poisonousDamage;
	float _poisonousTime;
	float _damageRadius;

	void setDamage(float damage, float poisonousDamage , float poisonousTime, float damageRadius);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();

	cocos2d::ParticleSystem* ps;

	void update(float delta);

};

