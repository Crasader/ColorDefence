#pragma once

#include "Bullet.h"


class BulletTypeExplodeOnDeath : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeExplodeOnDeath);

	float _explodeRadius;
	float _explodeDamage;

	void setDamage(float damage, float explodeRadius , float explodeDamage);

protected:


	virtual void explode();


};

