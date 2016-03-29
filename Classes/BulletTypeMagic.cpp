#include "BulletTypeMagic.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BulletTypeMagic::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setVisible(false);
	setVisible(true);


	/*
	RotateBy* rot = RotateBy::create(0.1f,500);
	RepeatForever* rept = RepeatForever::create(rot);
	runAction(rept);
	*/




	return true;
}



void BulletTypeMagic::explode()
{

	float damageContributed = _target->onMagicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
	starEmitter->setEmissionRate(0);
	
	unscheduleUpdate();

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}



void BulletTypeMagic::setTarget( Enemy* enemy )
{
	_target = enemy;

	//粒子系统 特效
	starEmitter = ParticleSystemQuad::create("effects/Particle_Bullet_Magic.plist");
	starEmitter->setPosition(getContentSize().width/2,getContentSize().height/2);
	
	(getParent())->addChild(starEmitter);
	//addChild(starEmitter);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(starEmitter);
	

	scheduleUpdate();



}

void BulletTypeMagic::update( float delta )
{

	if ((_target->isFloating)||(!_target->isAlive()))
	{
		explode();
		return;
	}
			


	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	//setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	dir = 9*dir;
	setPosition(getPosition()+dir);
	

	starEmitter->setPosition(getPosition());


	if (getPosition().getDistance(_target->getPosition())<20)
	{
		explode();
	}


}
