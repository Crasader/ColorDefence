#include "BulletTypeLargeWave.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"


USING_NS_CC;

bool BulletTypeLargeWave::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_LargeWave.png");
	setOpacity(0);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	em = EnemyManager::getInstance();
	enemiesDamaged = Vector<Enemy*>();

	_damageWidth = 90;
	setScale(_damageWidth/180.0);

	return true;
}


void BulletTypeLargeWave::setTarget( Enemy* enemy )
{

	Vec2 v = Vec2(enemy->getPosition()- getPosition());
	v.normalize();
	v = v* 2000;
	
	auto mv = MoveBy::create(2.2f,v);
	auto expld = CallFunc::create([&]{

		explode();

	});

	//粒子系统 特效
	emitter = ParticleSystemQuad::create("effects/Particle_LargeWave.plist");
	emitter->setPosition(getContentSize().width/2,getContentSize().height/2);
	(getParent())->addChild(emitter);
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);


	schedule(schedule_selector(BulletTypeLargeWave::update), 1.0f/60.0f);

	runAction(Sequence::create(mv,expld,NULL));


}

void BulletTypeLargeWave::explode()
{
	emitter->setEmissionRate(0);


	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeLargeWave::setDamage( float damage , float damageWidth )
{
	_damage = damage;
	_damageWidth = damageWidth;
	setScale(_damageWidth/180.0);
}


void BulletTypeLargeWave::update( float delta )
{

	if (_damageWidth < 480)
	{
		_damageWidth+=2.6f;
		setScale(_damageWidth/180.0);
	}


	for (Enemy* e : em->enemiesInSequence)
	{
		if (!enemiesDamaged.contains(e))
		{
			if (getPosition().getDistance(e->getPosition())<_damageWidth)
			{
				enemiesDamaged.pushBack(e);
				float damageContributed = e->onMagicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			}
		}

	}

	emitter->setPosition(getPosition());

}






