#include "BulletTypeArmorRemover.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "BuffTypeBroken.h"

USING_NS_CC;

bool BulletTypeArmorRemover::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	//setTexture("effects/Bullet_Splash.png");


	_damageRadius = 0;

	return true;
}



void BulletTypeArmorRemover::explode()
{
	//Point pt = _target->getPosition();
	Point pt = getPosition();
	EnemyManager* em  = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if (pt.getDistance(e->getPosition())<_damageRadius)
		{

			bool bBuff = e->setBuff(BuffTypeBroken::create(_target,_armorReduce,_brokenTime, true));
			float damageContributed = e->onPhysicalDamaged(_damage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);


			if (bBuff)
			{
				Sprite* rmvr = Sprite::create("effects/Bullet_ArmorRemover.png");
				rmvr->setPosition(e->getPosition());
				getParent()->addChild(rmvr);
				v_removers.pushBack(rmvr);

			}

		}

	}


	for (auto rmvr:v_removers)
	{
		auto s_ex1 = ScaleTo::create(0.3f,0.2f);
		auto s_ex2 = MoveTo::create(0.3f,getPosition());
		auto s_ex3 = Spawn::create(s_ex1,s_ex2,NULL);
		auto s_ex4 = FadeOut::create(0.1f);

		rmvr->runAction(Sequence::create(s_ex3,s_ex4,NULL));
	}



	//¶¯»­
	setTexture("effects/Bullet_ArmorRemover.png");
	float ratio = 2*_damageRadius / getContentSize().height;
	setScale(ratio);


	auto ex1 = FadeOut::create(0.5);
	auto ex2 = ScaleBy::create(0.5,0.25);
	auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		for (auto rmvr:v_removers)
		{
			rmvr->removeFromParent();
		}
		v_removers.clear();
		removeFromParent();
	});

	runAction(Sequence::create(ex3,ex4,NULL));



}

void BulletTypeArmorRemover::setDamage( float damage , float damageRaius , float armorReduce , float brokenTime)
{
	_damage = damage;
	_damageRadius = damageRaius;
	_armorReduce = armorReduce;
	_brokenTime = brokenTime;
}

void BulletTypeArmorRemover::setTarget( Enemy* enemy )
{
	_target = enemy;

	explode();


}

void BulletTypeArmorRemover::pause()
{
	Bullet::pause();
	for (auto rmvr:v_removers)
	{
		rmvr->pause();
	}
}

void BulletTypeArmorRemover::resume()
{
	Bullet::resume();
	for (auto rmvr:v_removers)
	{
		rmvr->resume();
	}
}


