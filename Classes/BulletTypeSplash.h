#pragma once

#include "Bullet.h"


class BulletTypeSplash : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeSplash);

	float _damageRadius;

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

