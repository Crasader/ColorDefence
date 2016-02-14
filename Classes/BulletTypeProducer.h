#pragma once

#include "Bullet.h"


class BulletTypeProducer : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeProducer);

	virtual void setTarget(Enemy* enemy, cocos2d::Point startPoint);


protected:

	cocos2d::Point _startingPoint;


	virtual void explode();
	void backToStartingPoint();

private:

	void update(float delta);

	cocos2d::ParticleSystem* emitter;

};

