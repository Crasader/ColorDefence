#pragma once

#include "Bullet.h"


class BulletTypeTrapping : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeTrapping);


	void setDamage(float damage , bool trapping);

protected:


	virtual void explode();

	bool _isTrapping;

};

