#include "BulletTypeSlowOne.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"
#include "BuffTypeSlow.h"

USING_NS_CC;

bool BulletTypeSlowOne::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_SlowOne.png");


	_slowFactor = 1;
	_slowTime = 1;

	return true;
}



void BulletTypeSlowOne::explode()
{
	
	emitter->setEmissionRate(0);
	_target-> onPhysicalDamaged(_damage);

	//_target->setBuffSlow(_slowFactor,_slowTime);
	_target->setBuff(BuffTypeSlow::create(_target , _slowFactor,_slowTime));

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeSlowOne::setDamage( float damage, float slowFactor , float slowTime )
{
	_damage = damage;
	_slowFactor = slowFactor;
	_slowTime = slowTime;
}

void BulletTypeSlowOne::setTarget( Enemy* enemy )
{
	_target = enemy;


	//����ϵͳ ��Ч
	emitter = ParticleSystemQuad::create("effects/Particle_Slow.plist");
	emitter->setPosition(getContentSize().width/2,getContentSize().height/2);
	(getParent())->addChild(emitter);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);

	scheduleUpdate();
}

void BulletTypeSlowOne::update( float delta )
{

	if ((_target->isFloating)||(!_target->isAlive()))
	{
		explode();
		return;
	}


	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	dir = 10*dir;
	setPosition(getPosition()+dir);

	emitter->setPosition(getPosition());


	if (getPosition().getDistance(_target->getPosition())<20)
	{
		explode();
	}

}




