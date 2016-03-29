#pragma once

#include "Bullet.h"
#include "Enemy.h"


class BulletTypeSlowOne : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
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

