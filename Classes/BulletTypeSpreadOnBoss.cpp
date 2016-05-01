#include "BulletTypeSpreadOnBoss.h"
#include "BulletManager.h"
#include "BuffTypeSpreadDamage.h"

USING_NS_CC;

bool BulletTypeSpreadOnBoss::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_SpreadOnBoss.png");


	return true;
}



void BulletTypeSpreadOnBoss::explode()
{

	auto buff = BuffTypeSpreadDamage::create(_target,3.0f,_spreadDamage);
	buff->setDamageContributerID(_damageContributerID);
	_target->setBuff(buff);
	
	
	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
	
	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);



}

void BulletTypeSpreadOnBoss::setDamage(float damage , float spreadDamage)
{
	_damage = damage;
	_spreadDamage = spreadDamage;


}

