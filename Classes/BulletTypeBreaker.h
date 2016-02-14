#pragma once

#include "Bullet.h"


class BulletTypeBreaker : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeBreaker);

	float _armorReduce;
	float _brokenTime;

	void setDamage(float damage, float armorReduce , float brokenTime);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

