#pragma once

#include "Bullet.h"


class BulletTypeDuplicate : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeDuplicate);

	float _damageRadius;

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

