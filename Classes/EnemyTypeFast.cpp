#include "EnemyTypeFast.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool EnemyTypeFast::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}


	getEquipment()->setTexture("enemies/type_fast_01.png");
	getEquipment()->setPosition(getAppearance()->getContentSize()/2);
	//MotionStreak* ms = MotionStreak::create(3,30,30,Color3B(255,0, 0), "effects/Bullet.png");
	particles = ParticleSystemQuad::create("effects/Particle_Exhaust.plist");

	particles->setPosition(0,0);
	addChild(particles,-1);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(particles);










	return true;
}



void EnemyTypeFast::setEnemyParameter(int hp, float ms, float arm )
{

	_moveSpeedFull = ms*2.0+0.2;
	moveSpeed = _moveSpeedFull;

	_armorFull = 0;
	_armor = _armorFull;

	_fullHitPoint = hp;
	_hitPoint = _fullHitPoint;




}




