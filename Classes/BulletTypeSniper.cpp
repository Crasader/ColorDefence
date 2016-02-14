#include "BulletTypeSniper.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BulletTypeSniper::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Sniper.png");
	//setVisible(false);


	return true;
}





void BulletTypeSniper::setDamage( float damage)
{
	_damage = damage;
	if (getPosition().getDistance(_target->getPosition())<180)
	{
		_damage = damage/2 ;
	}

}

void BulletTypeSniper::explode()
{
	_target->onPhysicalDamaged(_damage);
	if ((_target->getRestHitPointRate()<=0.16)&&(_target->isAlive()))
	{
		_target->onRealDamaged(1000000);
		setTexture("effects/Bullet_Sniper_headshot.png");
		setColor(Color3B(255,255,255));
		setScale(3);
		auto ex1 = FadeOut::create(0.5);
		auto ex4 = CallFunc::create([&]{
			BulletManager::getInstance()->bullets.eraseObject(this);
			removeFromParent();
		});

		runAction(Sequence::create(ex1,ex4,NULL));
		return;
	}
	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}
