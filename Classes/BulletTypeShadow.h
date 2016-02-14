#pragma once

#include "Bullet.h"


class BulletTypeShadow : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeShadow);

	float _damageRadius;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

