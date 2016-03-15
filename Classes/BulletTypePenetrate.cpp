#include "BulletTypePenetrate.h"
#include "BulletManager.h"


USING_NS_CC;

bool BulletTypePenetrate::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Penetrate.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	em = EnemyManager::getInstance();
	enemiesDamaged = Vector<Enemy*>();

	_damageWidth = 90;

	return true;
}


void BulletTypePenetrate::setTarget( Enemy* enemy )
{

	Vec2 v = Vec2(enemy->getPosition()- getPosition());
	v.normalize();
	v = v* 2000;
	
	auto mv = MoveBy::create(2,v);
	auto expld = CallFunc::create([&]{
		
		explode();

	});

	schedule(schedule_selector(BulletTypePenetrate::update), 1.0f/60.0f);
	runAction(Sequence::create(mv,expld,NULL));


}

void BulletTypePenetrate::explode()
{

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypePenetrate::setDamage( float damage , float damageWidth )
{
	_damage = damage;
	_damageWidth = damageWidth;
}


void BulletTypePenetrate::update( float delta )
{
	for (Enemy* e : em->enemiesInSequence)
	{
		if (!enemiesDamaged.contains(e))
		{
			if (getPosition().getDistance(e->getPosition())<_damageWidth)
			{
				enemiesDamaged.pushBack(e);
				float damageContributed = e->onPhysicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			}
		}

	}
}






