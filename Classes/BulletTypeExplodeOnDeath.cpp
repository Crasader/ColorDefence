#include "BulletTypeExplodeOnDeath.h"
#include "BulletManager.h"
#include "BuffTypePoisoning.h"
#include "BuffTypeExplodeOnDeath.h"


USING_NS_CC;

bool BulletTypeExplodeOnDeath::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_ExplodeOnDeath.png");

	_explodeRadius = 1;
	_explodeDamage = 1;

	return true;
}



void BulletTypeExplodeOnDeath::explode()
{
	

	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

	//_target->setBuffPoisoning(_poisonousDamage,_poisonousTime);
	
	
	auto buff = BuffTypeExplodeOnDeath::create(_target, _explodeRadius, _explodeDamage, 135);
	buff->setDamageContributerID(_damageContributerID);
	_target->setBuff(buff);

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeExplodeOnDeath::setDamage(float damage, float explodeRadius , float explodeDamage)
{
	_damage = damage;
	_explodeRadius = explodeRadius;
	_explodeDamage = explodeDamage;
}





