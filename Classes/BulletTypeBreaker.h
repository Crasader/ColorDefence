#pragma once

#include "Bullet.h"


class BulletTypeBreaker : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeBreaker);

	float _armorReduce;
	float _brokenTime;

	void setDamage(float damage, float armorReduce , float brokenTime);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

