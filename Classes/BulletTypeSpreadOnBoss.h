#pragma once

#include "Bullet.h"


class BulletTypeSpreadOnBoss : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeSpreadOnBoss);

	void setDamage(float damage);

protected:


	virtual void explode();


};

