#pragma once

#include "Bullet.h"


class BulletTypeMagic : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeMagic);

	virtual void setTarget(Enemy* enemy);


protected:


	virtual void explode();


private:

	void update(float delta);

	cocos2d::ParticleSystem* starEmitter;

};

