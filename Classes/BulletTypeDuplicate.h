#pragma once

#include "Bullet.h"


class BulletTypeDuplicate : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeDuplicate);

	float _damageRadius;

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

