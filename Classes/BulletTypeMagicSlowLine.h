#pragma once

#include "Bullet.h"
#include "EnemyManager.h"


class BulletTypeMagicSlowLine : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(BulletTypeMagicSlowLine);

	float _damageWidth;

	void setDamage(float damage , float damageWidth, float slowFactor , float slowTime);

	virtual void setTarget(Enemy* enemy);

protected:

	float _slowFactor;
	float _slowTime;

	virtual void explode();


	void update(float delta);


	EnemyManager* em;
	cocos2d::Vector<Enemy*> enemiesDamaged;

};

