#pragma once

#include "Bullet.h"


class BulletTypeSniper : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeSniper);

	void setDamage(float damage);




private:

	void explode();







};

