#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "SoundManager.h"


class Bullet : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
	CREATE_FUNC(Bullet);


	virtual void setTarget(Enemy* enemy);

	Enemy* getTarget();

	void setDamage(float d);


	virtual void pause();
	virtual void resume();

protected:

	

	float _damage;



	//������Ŀ��
	Enemy* _target;

	virtual void explode();

};

