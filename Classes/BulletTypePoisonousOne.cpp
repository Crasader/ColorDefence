#include "BulletTypePoisonousOne.h"
#include "BulletManager.h"
#include "BuffTypePoisoning.h"


USING_NS_CC;

bool BulletTypePoisonousOne::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_PoisonousOne.png");

	_poisonousDamage = 1;
	_poisonousTime = 1;

	return true;
}



void BulletTypePoisonousOne::explode()
{
	

	_target-> onPhysicalDamaged(_damage);

	//_target->setBuffPoisoning(_poisonousDamage,_poisonousTime);
	_target->setBuff(BuffTypePoisoning::create(_target,_poisonousDamage,_poisonousTime));

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypePoisonousOne::setDamage( float damage, float poisonousDamage , float poisonousTime )
{
	_damage = damage;
	_poisonousDamage = poisonousDamage;
	_poisonousTime = poisonousTime;
}





