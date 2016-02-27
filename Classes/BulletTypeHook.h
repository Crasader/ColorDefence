#pragma once

#include "Bullet.h"


class BulletTypeHook : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeHook);

	bool _catching;

	void setDamage(float damage, bool catching);

	void setTarget(Enemy* enemy);

protected:


	virtual void explode();



};

