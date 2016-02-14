#include "BulletTypeSplash.h"
#include "EnemyManager.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeSplash::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_damageRadius = 0;

	return true;
}



void BulletTypeSplash::explode()
{
	//Point pt = _target->getPosition();
	Point pt = getPosition();
	EnemyManager* em  = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if (pt.getDistance(e->getPosition())<_damageRadius)
		{
			e-> onPhysicalDamaged(_damage);
		}
	}

	//¶¯»­
	setTexture("effects/splash.png");
	float ratio = 2*_damageRadius / getContentSize().height;
	setScale(ratio);

	auto ex1 = FadeOut::create(0.5);
	//auto ex2 = RotateBy::create(0.5,-72);
	//auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex1,ex4,NULL));



}

void BulletTypeSplash::setDamage( float damage , float damageRaius )
{
	_damage = damage;
	_damageRadius = damageRaius;
}


