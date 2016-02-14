#pragma once

#include "Bullet.h"
#include "Cannon.h"


class BulletTypeBridge : public Bullet
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(BulletTypeBridge);


	void setDamage(float damage,bool bridging,float damageRadius);

	void setTarget(Cannon* cannon);
	void setTarget(Enemy* enemy);

protected:

	Cannon* _targetCannon;

	virtual void explode();
	virtual void bridge();

	bool _bridging;
	float _damageRadius;

	void update(float delta);

};

