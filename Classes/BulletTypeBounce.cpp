#include "BulletTypeBounce.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"
#include "BuffTypeSlow.h"

USING_NS_CC;

bool BulletTypeBounce::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Splash.png");


	_bounceRange = 0;
	_damageReduceFactor = 1;
	_bounceTimes = 0;

	return true;
}



void BulletTypeBounce::explode()
{

	_snow->setEmissionRate(0);



	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);


}

void BulletTypeBounce::setDamage(float damage , float bounceRange, float damageReduceFactor, int bounceTimes )
{
	_damage = damage;
	_bounceRange = bounceRange;
	_damageReduceFactor = damageReduceFactor;
	_bounceTimes = bounceTimes;




}

void BulletTypeBounce::bounce()
{

	_target->onPhysicalDamaged(_damage);
	_target->setBuff(BuffTypeSlow::create(_target , 0.4f , 60));
	targetsBouncedOver.pushBack(_target);

	if (_bounceTimes == 0)
	{
		explode();
		return;
	}
	


	Vector<Enemy*> eis = EnemyManager::getInstance()->enemiesInSequence;
	///////
	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: eis)
	{
		if ((!targetsBouncedOver.contains(e))&&(getPosition().getDistance(e->getPosition())<=_bounceRange))
		{
			v_target.pushBack(e);
		}
	}


	if (v_target.empty())
	{
		unscheduleUpdate();
		_target = nullptr;
		explode();
		return;
	}


	_target = v_target.front();

	for (Enemy*e : v_target)
	{
		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_target->getPosition()))
		{
			_target = e;
		}
	}


	_bounceTimes -- ;
	_damage = _damage * _damageReduceFactor;


}

void BulletTypeBounce::setTarget( Enemy* enemy )
{
	_target = enemy;


	//粒子系统 特效
	_snow = ParticleSystemQuad::create("effects/Particle_Slow.plist");
	_snow->setPosition(getContentSize().width/2,getContentSize().height/2);
	(getParent())->addChild(_snow);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(_snow);
	_snow->setTotalParticles(40);
	_snow->setEmissionRate(80);
	_snow->setLife(0.2f);
	_snow->setLifeVar(0);
	_snow->setSpeed(0);
	_snow->setPosVar(Vec2(0,0));



	scheduleUpdate();

}

void BulletTypeBounce::update( float delta )
{


	if ((_target->isFloating)||(!_target->isAlive()))
	{
		explode();
		return;
	}



	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();

	dir = 5*dir;
	setPosition(getPosition()+dir);


	_snow->setPosition(getPosition());


	if (getPosition().getDistance(_target->getPosition())<20)
	{
		
		bounce();
	}



}


