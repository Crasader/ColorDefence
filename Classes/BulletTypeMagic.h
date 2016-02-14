#pragma once

#include "Bullet.h"


class BulletTypeMagic : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeMagic);

	virtual void setTarget(Enemy* enemy);


protected:


	virtual void explode();


private:

	void update(float delta);

	cocos2d::ParticleSystem* starEmitter;

};

