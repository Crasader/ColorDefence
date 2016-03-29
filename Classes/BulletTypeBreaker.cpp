#include "BulletTypeBreaker.h"
#include "BulletManager.h"
#include "BuffTypeBroken.h"


USING_NS_CC;

bool BulletTypeBreaker::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);


	_armorReduce = 1;
	_brokenTime = 1;

	return true;
}



void BulletTypeBreaker::explode()
{
	

	//_target->setBuffBroken(_armorReduce,_brokenTime);

	_target->setBuff(BuffTypeBroken::create(_target,_armorReduce,_brokenTime , false));

	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

	

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeBreaker::setDamage(float damage, float armorReduce , float brokenTime)
{
	_damage = damage;
	_armorReduce = armorReduce;
	_brokenTime = brokenTime;
}

void BulletTypeBreaker::setTarget( Enemy* enemy )
{

	_target = enemy;
	explode();
}







