#pragma once

#include "Bullet.h"


class BulletTypeArmorRemover : public Bullet
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(BulletTypeArmorRemover);

	float _damageRadius;
	float _armorReduce;
	float _brokenTime;

	void setTarget(Enemy* enemy);

	void setDamage(float damage , float damageRaius, float armorReduce , float brokenTime);


	void pause();
	void resume();


protected:


	virtual void explode();

private:
	cocos2d::Vector<cocos2d::Sprite*> v_removers;

};

