#include "BulletTypePoisonousMulti.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"
#include "BuffTypePoisoning.h"

USING_NS_CC;

bool BulletTypePoisonousMulti::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_damageRadius = 0;
	_poisonousDamage = 1;
	_poisonousTime = 1;

	setOpacity(0);


	enemiesDamaged = Vector<Enemy*>();
	em = EnemyManager::getInstance();
	_damageWidth = 10;

	return true;
}



void BulletTypePoisonousMulti::explode()
{
	//ps->removeFromParent();
	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);


}

void BulletTypePoisonousMulti::setDamage( float damage , float damageRaius, float poisonousDamage , float poisonousTime )
{
	_damage = damage;
	_damageRadius = damageRaius;
	_poisonousDamage = poisonousDamage;
	_poisonousTime = poisonousTime;


	ps = ParticleSystemQuad::create("effects/Particle_Bullet_PoisonousMulti.plist");

	getParent()->addChild(ps,10);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(ps);


	Vec2 v = Vec2(sin(CC_DEGREES_TO_RADIANS(getRotation())),cos(CC_DEGREES_TO_RADIANS(getRotation())));
	//Vec2 v = Vec2(cos((getRotation()+0)),sin((getRotation()+0)));
	v.normalize();
	v = v* 20;

	
	ps->setRotation(getRotation());
	ps->setPosition(getPosition()+v);

	ps->setSpeed(damageRaius*1.2 - 20);

	ps->setEmissionRate(damageRaius*3);
	ps->setLife(0.9*_damageRadius/170);


}

void BulletTypePoisonousMulti::setTarget( Enemy* enemy )
{

	//_target = enemy;

	Vec2 v = Vec2(enemy->getPosition()- getPosition());
	v.normalize();
	v = v* _damageRadius * 0.6;
	float t = 0.0050*_damageRadius;

	auto mv = MoveBy::create(t,v);
	auto expld = CallFunc::create([&]{

		explode();

	});

	scheduleUpdate();
	runAction(Sequence::create(mv,expld,NULL));



}


void BulletTypePoisonousMulti::update( float delta )
{

	_damageWidth += 144.0 * delta;


	for (Enemy* e : em->enemiesInSequence)
	{
		if (!enemiesDamaged.contains(e))
		{
			if (getPosition().getDistance(e->getPosition())<_damageWidth)
			{
				enemiesDamaged.pushBack(e);
				float damageContributed = e->onPhysicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
				
				auto buff = BuffTypePoisoning::create(e,_poisonousDamage,_poisonousTime);
				buff->setDamageContributerID(_damageContributerID);
				e->setBuff(buff);
			}
		}

	}



}


