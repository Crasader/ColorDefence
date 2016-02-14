#pragma once

#include "Bullet.h"


class BulletTypeSuperPoisonous : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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

