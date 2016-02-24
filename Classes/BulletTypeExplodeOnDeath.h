#pragma once

#include "Bullet.h"


class BulletTypeExplodeOnDeath : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeExplodeOnDeath);

	float _explodeRadius;
	float _explodeDamage;

	void setDamage(float damage, float explodeRadius , float explodeDamage);

protected:


	virtual void explode();


};

