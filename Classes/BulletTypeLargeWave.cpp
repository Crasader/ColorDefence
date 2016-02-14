#include "BulletTypeLargeWave.h"
#include "BulletManager.h"


USING_NS_CC;

bool BulletTypeLargeWave::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_LargeWave.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	em = EnemyManager::getInstance();
	enemiesDamaged = Vector<Enemy*>();

	_damageWidth = 90;
	setScale(_damageWidth/180.0);

	return true;
}


void BulletTypeLargeWave::setTarget( Enemy* enemy )
{

	Vec2 v = Vec2(enemy->getPosition()- getPosition());
	v.normalize();
	v = v* 2000;
	
	auto mv = MoveBy::create(2.2f,v);
	auto expld = CallFunc::create([&]{
		
		explode();

	});

	scheduleUpdate();
	runAction(Sequence::create(mv,expld,NULL));


}

void BulletTypeLargeWave::explode()
{

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeLargeWave::setDamage( float damage , float damageWidth )
{
	_damage = damage;
	_damageWidth = damageWidth;
	setScale(_damageWidth/180.0);
}


void BulletTypeLargeWave::update( float delta )
{

	if (_damageWidth < 480)
	{
		_damageWidth+=2.6f;
		setScale(_damageWidth/180.0);
	}


	for (Enemy* e : em->enemiesInSequence)
	{
		if (!enemiesDamaged.contains(e))
		{
			if (getPosition().getDistance(e->getPosition())<_damageWidth)
			{
				enemiesDamaged.pushBack(e);
				e->onPhysicalDamaged(_damage);
			}
		}

	}
}






