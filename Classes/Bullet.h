#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "SoundManager.h"


class Bullet : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(Bullet);


	virtual void setTarget(Enemy* enemy);

	Enemy* getTarget();

	void setDamage(float d);


	virtual void pause();
	virtual void resume();

protected:

	

	float _damage;



	//攻击的目标
	Enemy* _target;

	virtual void explode();

};

