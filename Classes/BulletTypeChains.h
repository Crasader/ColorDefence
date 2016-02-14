#pragma once

#include "Bullet.h"


class BulletTypeChains : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeChains);

	void setTarget(Enemy* enemy);


	void setDamage(float dmg , float stunTime);

private:

	void explode();

	float _stunTime;

};

