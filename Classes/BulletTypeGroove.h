#pragma once

#include "Bullet.h"


class BulletTypeGroove : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeGroove);

	void setTarget(Enemy* enemy);


	void setDamage(float dmg , float stunTime ,float grooveLength);

private:

	void explode();

	float _stunTime;
	float _grooveLength;

	virtual void update(float delta);

	cocos2d::Point _end[2]; 
	

	cocos2d::Vector<Enemy*> _blocked;

};

