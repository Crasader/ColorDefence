#pragma once

#include "Bullet.h"


class BulletTypeShadow : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeShadow);

	float _damageRadius;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();

private:

private:
	cocos2d::Vector<cocos2d::Sprite*> v_explodes;

};

