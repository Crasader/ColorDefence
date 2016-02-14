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

	setTexture("effects/Bullet_Focus.png");


	return true;
}



void BulletTypeSpreadOnBoss::explode()
{

	_target->setBuff(BuffTypeSpreadDamage::create(_target,180));
	
	_target->onPhysicalDamaged(_damage);
	
	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);



}

void BulletTypeSpreadOnBoss::setDamage(float damage)
{
	_damage = damage;


}

