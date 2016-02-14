#pragma once

#include "Bullet.h"


class BulletTypeConsumer : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
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

