#include "BulletTypeHook.h"
#include "BulletManager.h"



USING_NS_CC;

bool BulletTypeHook::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);


	_catching = false;


	return true;
}



void BulletTypeHook::explode()
{
	


	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

	

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeHook::setDamage(float damage,  bool catching)
{
	_damage = damage;
	_catching = catching;

}

void BulletTypeHook::setTarget( Enemy* enemy )
{

	_target = enemy;
	explode();
}







