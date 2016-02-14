#pragma once

#include "Bullet.h"


class BulletTypeChains : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeChains);

	void setTarget(Enemy* enemy);


	void setDamage(float dmg , float stunTime);

private:

	void explode();

	float _stunTime;

};

