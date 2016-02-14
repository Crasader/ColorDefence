#pragma once

#include "Bullet.h"


class BulletTypeBreaker : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeBreaker);

	float _armorReduce;
	float _brokenTime;

	void setDamage(float damage, float armorReduce , float brokenTime);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

