#pragma once

#include "Bullet.h"


class BulletTypeSpiral : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeSpiral);

	float _damageRadius;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

