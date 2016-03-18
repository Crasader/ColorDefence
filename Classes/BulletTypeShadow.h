#pragma once

#include "Bullet.h"


class BulletTypeShadow : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
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

