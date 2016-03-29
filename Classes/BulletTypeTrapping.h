#pragma once

#include "Bullet.h"


class BulletTypeTrapping : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeTrapping);


	void setDamage(float damage , bool trapping);

protected:


	virtual void explode();

	bool _isTrapping;

};

