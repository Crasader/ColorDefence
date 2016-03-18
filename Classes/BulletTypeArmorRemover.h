#pragma once

#include "Bullet.h"


class BulletTypeArmorRemover : public Bullet
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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

