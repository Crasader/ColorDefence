#pragma once

#include "Bullet.h"


class BulletTypeSplash : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeSplash);

	float _damageRadius;

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

