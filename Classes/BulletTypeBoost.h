#pragma once

#include "Bullet.h"
#include "Cannon.h"


class BulletTypeBoost : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeBoost);


	void setDamage(float damage);

	void setTarget(Cannon* cannon);

protected:

	Cannon* _targetCannon;

	virtual void explode();


};

