#pragma once

#include "Bullet.h"


class BulletTypeExplodeOnDeath : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeExplodeOnDeath);

	float _explodeRadius;
	float _explodeDamage;

	void setDamage(float damage, float explodeRadius , float explodeDamage);

protected:


	virtual void explode();


};

