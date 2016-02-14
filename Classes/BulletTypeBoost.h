#pragma once

#include "Bullet.h"
#include "Cannon.h"


class BulletTypeBoost : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeBoost);


	void setDamage(float damage);

	void setTarget(Cannon* cannon);

protected:

	Cannon* _targetCannon;

	virtual void explode();


};

