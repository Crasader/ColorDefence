#pragma once

#include "Bullet.h"


class BulletTypeMagic : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeMagic);

	virtual void setTarget(Enemy* enemy);


protected:


	virtual void explode();


private:

	void update(float delta);

	cocos2d::ParticleSystem* starEmitter;

};

