#pragma once

#include "Bullet.h"


class BulletTypeChains : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeChains);

	void setTarget(Enemy* enemy);


	void setDamage(float dmg , float stunTime);

private:

	void explode();

	float _stunTime;

};

