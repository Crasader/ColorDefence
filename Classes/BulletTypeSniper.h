#pragma once

#include "Bullet.h"


class BulletTypeSniper : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeSniper);

	void setDamage(float damage);




private:

	void explode();







};

