#pragma once

#include "Bullet.h"


class BulletTypePoisonousOne : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypePoisonousOne);

	float _poisonousDamage;
	float _poisonousTime;

	void setDamage(float damage, float poisonousDamage , float poisonousTime);

	//void setTarget(Enemy* enemy);

protected:


	virtual void explode();

	//void update(float delta);

};

