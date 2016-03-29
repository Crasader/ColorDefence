#pragma once

#include "Bullet.h"


class BulletTypeFocus : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeFocus);

	bool _isSight;

	void setDamage(float damage , bool isSight);

protected:


	virtual void explode();

	void update(float delta);

};

