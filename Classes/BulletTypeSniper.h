#pragma once

#include "Bullet.h"


class BulletTypeSniper : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeSniper);

	void setDamage(float damage);




private:

	void explode();







};

