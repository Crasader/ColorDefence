#pragma once

#include "Bullet.h"


class BulletTypeFlower : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeFlower);

	float _damageRadius;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius);

	void setPetalColor(cocos2d::Color3B c3b);


	void pause();
	void resume();

private:

	cocos2d::Sprite* _petal[5];

	void explode();

	void bloom();

	void performDamage();


};