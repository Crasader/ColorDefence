#include "BulletTypeSpiral.h"
#include "EnemyManager.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeSpiral::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Spiral_off.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_damageRadius = 0;
	_extraState = false;

	return true;
}



void BulletTypeSpiral::explode()
{
	//Point pt = _target->getPosition();
	Point pt = getPosition();

	if (_extraState)
	{
		EnemyManager* em  = EnemyManager::getInstance();
		for (Enemy* e : em->enemiesInSequence)
		{
			if (pt.getDistance(e->getPosition())<_damageRadius)
			{
				float damageContributed = e->onPhysicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

			}

		}



	}
	else
	{
		EnemyManager* em  = EnemyManager::getInstance();
		int total = 0;
		Vector<Enemy*> targets = Vector<Enemy*>();
		for (Enemy* e : em->enemiesInSequence)
		{
			if (pt.getDistance(e->getPosition())<_damageRadius)
			{
				total ++;
				targets.pushBack(e);

			}

		}
		if (total != 0)
		{
			_damage = _damage / (float)total;
			for (Enemy* e : targets)
			{
				float damageContributed = e->onPhysicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			}
		}




	}

	//动画
	float ratio = 1.6*_damageRadius / getContentSize().height;
	setScale(ratio);

	auto ex1 = FadeOut::create(0.5);
	auto ex2 = RotateBy::create(0.5,_extraState?100:-20);
	auto ex3 = ScaleBy::create(0.5,_extraState?1.25:0.9);
	auto ex4 = Spawn::create(ex1,ex2,ex3,nullptr);

	auto ex5 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});


	runAction(Sequence::create(ex4,ex5,NULL));


}

void BulletTypeSpiral::setDamage( float damage , float damageRaius , bool extraState)
{
	_damage = damage;
	_damageRadius = damageRaius;
	_extraState = extraState;
	if (_extraState)
	{
		setTexture("effects/Bullet_Spiral_on.png");
	}
}

void BulletTypeSpiral::setTarget( Enemy* enemy )
{
	_target = enemy;

	explode();


}


