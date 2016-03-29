#include "BulletTypeTracing.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"


USING_NS_CC;

bool BulletTypeTracing::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Tracing.png");
	//setVisible(false);

	Sprite* cover = Sprite::create("effects/Bullet_Tracing_cover.png");
	addChild(cover);
	cover->setPosition(getContentSize()/2);
	cover->setOpacity(200);

	_damageFactor = 0.1;
	_speedFactor = 0.2;
	_damageMax = 10;
	_speedMax = 10;

	_initSpeed = 0;

	//runAction(RepeatForever::create(RotateBy::create(1,720)));

	setScale(0.01);
	runAction(ScaleTo::create(0.3,1));

	return true;
}



void BulletTypeTracing::explode()
{

	unscheduleUpdate();

	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
// 	if (_initSpeed>8)
// 	{
// 		_target->setBuffStun(30);
// 	}
	
	
	_tail->setEmissionRate(0);
	


	//log("damage = %f", _damage);
	
	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

	
}

void BulletTypeTracing::setDamage( float damage , float speedFactor , float damageFactor , float speedMax, float damageMax )
{
	_damage = damage;
	_damageFactor = damageFactor;
	_damageMax = damageMax;
	_speedFactor = speedFactor;
	_speedMax = speedMax;

	//log("base damage = %f", _damage);
}




void BulletTypeTracing::setTarget( Enemy* enemy )
{
	_target = enemy;

	//粒子系统 特效
	_tail = ParticleSystemQuad::create("effects/Particle_Tracing.plist");
	_tail->setPosition(getContentSize().width/2,getContentSize().height/2);
	Color3B c3b = getColor();
	_tail->setStartColor(Color4F((float)c3b.r/255,(float)c3b.g/255,(float)c3b.b/255,1));
	_tail->setEndColor(Color4F((float)c3b.r/255,(float)c3b.g/255,(float)c3b.b/255,1));


	(getParent())->addChild(_tail,-1);
	//addChild(starEmitter);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(_tail);

	scheduleUpdate();

}

void BulletTypeTracing::update( float delta )
{


	if ((_target->isFloating)||(!_target->isAlive()))
	{
		explode();
		return;
	}
	if (getPosition().getDistance(_target->getPosition())<20)
	{
		explode();
		return;
	}


	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();

	setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	
	dir = _initSpeed*dir;
	setPosition(getPosition()+dir);
	_tail->setPosition(getPosition());

	if (_initSpeed <= _speedMax)
	{
		_initSpeed+= _speedFactor;
	}
	if (_damage <= _damageMax)
	{
		_damage+= _damageFactor;
	}



}




