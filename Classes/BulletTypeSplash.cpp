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


	setTexture("effects/Bullet_Splash.png");
	//setScale(0.8);

	//Sprite* shell = Sprite::create("effects/Bullet_Splash.png");
	//addChild(shell,-1);
	//shell->setPosition(getContentSize()/2);
	


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

			float damageContributed = e->onPhysicalDamaged(_damage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

		}
	}

	//动画
	setTexture("effects/splash.png");
	float ratio = 2*_damageRadius / getContentSize().height;
	setScale(ratio * 0.3);

	auto ex0 = ScaleTo::create(0.1,ratio);
	auto ex1 = FadeOut::create(0.4);
	auto ex2 = ScaleTo::create(0.1,ratio*0.85);
	auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex0,ex3,ex4,NULL));



}

void BulletTypeSplash::setDamage( float damage , float damageRaius )
{
	_damage = damage;
	_damageRadius = damageRaius;
}


