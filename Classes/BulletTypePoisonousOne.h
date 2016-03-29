#pragma once

#include "Bullet.h"


class BulletTypePoisonousOne : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypePoisonousOne);

	float _poisonousDamage;
	float _poisonousTime;

	void setDamage(float damage, float poisonousDamage , float poisonousTime);

	//void setTarget(Enemy* enemy);

protected:


	virtual void explode();

	//void update(float delta);

};

