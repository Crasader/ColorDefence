#pragma once

#include "Bullet.h"


class BulletTypeTrapping : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeTrapping);


	void setDamage(float damage , bool trapping);

protected:


	virtual void explode();

	bool _isTrapping;

};

