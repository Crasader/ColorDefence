#pragma once

#include "Bullet.h"


class BulletTypeProducer : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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

