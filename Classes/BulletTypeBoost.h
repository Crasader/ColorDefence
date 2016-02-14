#pragma once

#include "Bullet.h"
#include "Cannon.h"


class BulletTypeBoost : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeBoost);


	void setDamage(float damage);

	void setTarget(Cannon* cannon);

protected:

	Cannon* _targetCannon;

	virtual void explode();


};

