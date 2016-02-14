#pragma once

#include "Bullet.h"


class BulletTypeTracing : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeTracing);

	

	void setDamage(float damage , float speedFactor , float damageFactor , float speedMax, float damageMax);

	void setTarget(Enemy* enemy);

protected:



	cocos2d::ParticleSystem* _tail;

	float _speedFactor;
	float _damageFactor;
	float _speedMax;
	float _damageMax;

	float _initSpeed;

	virtual void explode();

	void update(float delta);



};

