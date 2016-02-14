#pragma once

#include "Bullet.h"


class BulletTypeFocus : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeFocus);

	bool _isSight;

	void setDamage(float damage , bool isSight);

protected:


	virtual void explode();

	void update(float delta);

};

