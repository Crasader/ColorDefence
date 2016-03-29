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

			if (e->isAntiMagic())
			{

				Sprite* shadow_explode = Sprite::create("effects/effect_shadow_explode.png");
				shadow_explode->setPosition(e->getPosition());
				shadow_explode->setScale(3);
				shadow_explode->setColor(Color3B(70,70,70));
				getParent()->addChild(shadow_explode);
				v_explodes.pushBack(shadow_explode);
			}

		}

	}





	//整体的动画
	setTexture("effects/Bullet_Shadow.png");
	float ratio = 1.6*_damageRadius / getContentSize().height;
	setScale(ratio);

	auto ex1 = FadeOut::create(0.5);
	auto ex2 = ScaleBy::create(0.5,1.25);
	auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		for (auto shexp:v_explodes)
		{
			shexp->removeFromParent();
		}
		removeFromParent();
	});

	runAction(Sequence::create(ex3,ex4,NULL));


	//对于魔免怪的动画
	for (auto rmvr:v_explodes)
	{
		auto s_ex1 = ScaleTo::create(0.5f,0.5f);
		auto s_ex2 = FadeOut::create(0.5f);
		auto s_ex3 = RotateBy::create(0.5f,180);
		auto s_ex4 = Spawn::create(s_ex1,s_ex2,s_ex3,NULL);

		rmvr->runAction(s_ex4);
	}




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


