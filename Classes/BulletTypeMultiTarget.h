#pragma once

#include "Bullet.h"


class BulletTypeMultiTarget : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeMultiTarget);

	virtual void setTarget(Enemy* enemy);


protected:


	virtual void explode();


private:

	void update(float delta);

	cocos2d::ParticleSystem* starEmitter;

};

