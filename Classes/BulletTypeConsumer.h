#pragma once

#include "Bullet.h"


class BulletTypeConsumer : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeConsumer);

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius);

protected:

	float _damageRadius;

	virtual void explode();

	void update(float delta);

	cocos2d::Sprite* _childBullet[3];
	cocos2d::ParticleSystem* _childTail[3];



};

