#pragma once

#include "Bullet.h"


class BulletTypeHook : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeHook);

	bool _catching;

	void setDamage(float damage, bool catching);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

