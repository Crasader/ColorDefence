#pragma once

#include "Bullet.h"


class BulletTypeDuplicate : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeDuplicate);

	float _damageRadius;

	void setDamage(float damage , float damageRaius);

protected:


	virtual void explode();


};

