#pragma once

#include "Bullet.h"


class BulletTypeFlower : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
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