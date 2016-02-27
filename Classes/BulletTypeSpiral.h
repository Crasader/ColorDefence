#pragma once

#include "Bullet.h"


class BulletTypeSpiral : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeSpiral);

	float _damageRadius;
	bool _extraState;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius , bool extraState);

protected:


	virtual void explode();


};

