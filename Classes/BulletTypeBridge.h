#pragma once

#include "Bullet.h"
#include "Cannon.h"


class BulletTypeBridge : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
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

