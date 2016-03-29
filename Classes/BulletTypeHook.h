#pragma once

#include "Bullet.h"


class BulletTypeHook : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeHook);

	bool _catching;

	void setDamage(float damage, bool catching);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

