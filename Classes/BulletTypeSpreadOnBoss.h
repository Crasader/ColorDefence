#pragma once

#include "Bullet.h"


class BulletTypeSpreadOnBoss : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeSpreadOnBoss);

	void setDamage(float damage);

protected:


	virtual void explode();


};

