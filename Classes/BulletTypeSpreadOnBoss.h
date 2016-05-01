#pragma once

#include "Bullet.h"


class BulletTypeSpreadOnBoss : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeSpreadOnBoss);

	void setDamage(float damage , float spreadDamage);

protected:


	virtual void explode();
	float _spreadDamage;

};

