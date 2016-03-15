#include "BulletTypeSuperPoisonous.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "BuffTypeSuperPoisoning.h"
#include "ParticleEmitterManager.h"


USING_NS_CC;

bool BulletTypeSuperPoisonous::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setOpacity(0);

	_poisonousDamage = 1;
	_poisonousTime = 1;

	return true;
}



void BulletTypeSuperPoisonous::explode()
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
			auto buff = BuffTypeSuperPoisoning::create(_target,_poisonousDamage,_poisonousTime);
			buff->setDamageContributerID(_damageContributerID);
			e-> setBuff(buff);
		}
	}

	//动画
	unschedule(schedule_selector(BulletTypeSuperPoisonous::update));
	ps->setEmissionRate(0);
	ParticleSystem* explode = ParticleSystemQuad::create("effects/Particle_SuperPoisonous_explode.plist");
	(getParent())->addChild(explode,10086);
	explode->setPosition(getPosition());
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(explode);



	BulletManager::getInstance()->bullets.eraseObject(this);
	removeFromParent();



}

void BulletTypeSuperPoisonous::setDamage( float damage, float poisonousDamage , float poisonousTime , float damageRadius)
{
	_damage = damage;
	_poisonousDamage = poisonousDamage;
	_poisonousTime = poisonousTime;
	_damageRadius = damageRadius;
}

void BulletTypeSuperPoisonous::setTarget( Enemy* enemy )
{
	_target = enemy;


	//粒子系统 特效
	ps = ParticleSystemQuad::create("effects/Particle_Bullet_SuperPoisonous.plist");
	(getParent())->addChild(ps);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(ps);

	schedule(schedule_selector(BulletTypeSuperPoisonous::update), 1.0f/60.0f);



	MoveTo* move = MoveTo::create(0.75, _target->getPosition());
	ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeSuperPoisonous::explode,this));

	Sequence* sqe = Sequence::create(move,explode,NULL);

	runAction(sqe);
}

void BulletTypeSuperPoisonous::update( float delta )
{
	if (ps!=nullptr)
	{
		ps->setPosition(getPosition());
	}
	
}





