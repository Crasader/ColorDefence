#include "BulletTypeShadow.h"
#include "EnemyManager.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeShadow::init()
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



void BulletTypeShadow::explode()
{
	//Point pt = _target->getPosition();
	Point pt = getPosition();
	EnemyManager* em  = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if (pt.getDistance(e->getPosition())<_damageRadius)
		{
			float damageContributed = e->onShadowDamaged(_damage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			/*
			if (e->isAntiMagic())
			{
				Sprite* expld = Sprite::create("effects/shadow_explode.png");
				e->getEquipment()->addChild(expld,10086);
				expld->setPosition(e->getEquipment()->getContentSize()/2);
				auto s_ex1 = FadeOut::create(0.25);
				auto s_ex4 = CallFunc::create([&](){
					expld->removeFromParent();
					BulletManager::getInstance()->bullets.eraseObject(this);
					
				});
				expld->runAction(Sequence::create(s_ex1,s_ex4,NULL));
			}
			*/
		}

	}

	//����
	setTexture("effects/Bullet_Shadow.png");
	float ratio = 1.6*_damageRadius / getContentSize().height;
	setScale(ratio);

	auto ex1 = FadeOut::create(0.5);
	auto ex2 = ScaleBy::create(0.5,1.25);
	auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex3,ex4,NULL));



}

void BulletTypeShadow::setDamage( float damage , float damageRaius )
{
	_damage = damage;
	_damageRadius = damageRaius;
}

void BulletTypeShadow::setTarget( Enemy* enemy )
{
	_target = enemy;

	explode();


}


