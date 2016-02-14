#pragma once

#include "Bullet.h"
#include "EnemyManager.h"


class BulletTypePoisonousMulti : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypePoisonousMulti);

	float _damageRadius;
	float _poisonousDamage;
	float _poisonousTime;

	void setTarget(Enemy* enemy);
	void setDamage(float damage , float damageRaius , float _poisonousDamage , float _poisonousTime );

protected:


	virtual void explode();

	void update(float delta);
	cocos2d::Vector<Enemy*> enemiesDamaged;

	EnemyManager* em;

private:

	cocos2d::ParticleSystem* ps;
	float _damageWidth;
};

