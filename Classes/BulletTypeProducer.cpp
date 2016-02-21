#include "BulletTypeProducer.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"


USING_NS_CC;

bool BulletTypeProducer::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);


	return true;
}



void BulletTypeProducer::explode()
{

	setPosition(_target->getPosition());

	float damageContributed = _target->onPhysicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

	setVisible(false);
	

	//粒子系统 特效
	emitter = ParticleSystemQuad::create("effects/Particle_Producer.plist");
	emitter->setPosition(getContentSize().width/2,getContentSize().height/2);
	(getParent())->addChild(emitter);
	//addChild(emitter);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);

	SoundManager::getInstance()->playSoundEffect("sound/bullet_explode_producer.wav");

	scheduleUpdate();



}



void BulletTypeProducer::setTarget( Enemy* enemy , Point startPoint)
{
	_target = enemy;
	_startingPoint = startPoint;
	
	MoveTo* move = MoveTo::create(0.1, _target->getPosition());
	ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeProducer::explode,this));

	Sequence* sqe = Sequence::create(move,explode,NULL);

	runAction(sqe);


}

void BulletTypeProducer::update( float delta )
{


	Vec2 dir = _startingPoint - getPosition();
	dir.normalize();
	//setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	dir = 9*dir;
	setPosition(getPosition()+dir);
	

	emitter->setPosition(getPosition());


	if (getPosition().getDistance(_startingPoint)<30)
	{
		backToStartingPoint();
	}


}

void BulletTypeProducer::backToStartingPoint()
{
	emitter->setEmissionRate(0);

	unscheduleUpdate();

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);
}
