#pragma once

#include "Bullet.h"


class BulletTypeFocus : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeFocus);

	bool _isSight;

	void setDamage(float damage , bool isSight);

protected:


	virtual void explode();

	void update(float delta);

};

