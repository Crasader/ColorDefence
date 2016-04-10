#include "BulletTypeConsumer.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BulletTypeConsumer::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Splash.png");
	//setVisible(false);

	_damageRadius = 0;

	return true;
}



void BulletTypeConsumer::explode()
{

	unscheduleUpdate();
	removeAllChildren();
	for (int i = 0;i<3;i++)
	{
		//_childTail[i]->cleanup();
		_childTail[i]->setEmissionRate(0);
	}

	//Point pt = _target->getPosition();
	Point pt = getPosition();
	EnemyManager* em  = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if (pt.getDistance(e->getPosition())<_damageRadius)
		{
			float damageContributed = e->onPhysicalDamaged(_damage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
		}
	}

	//动画
	ParticleSystem* explode = ParticleSystemQuad::create("effects/Particle_Consumer_explode.plist");
	(getParent())->addChild(explode,10086);
	explode->setPosition(getPosition());
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(explode);



	BulletManager::getInstance()->bullets.eraseObject(this);
	removeFromParent();

	
	for (int i = 0 ; i<3 ; i++)
	{
		_childBullet[i] = nullptr;
		_childTail[i] = nullptr;
	}
	
	SoundManager::getInstance()->playSoundEffect("sound/bullet_explode_consumer.mp3");


}

void BulletTypeConsumer::setDamage( float damage , float damageRaius )
{
	_damage = damage;
	_damageRadius = damageRaius;
}

void BulletTypeConsumer::setTarget( Enemy* enemy )
{
	_target = enemy;

	for (int i = 0 ; i<3 ; i++)
	{
		_childBullet[i] = Sprite::create("effects/Bullet.png");
		addChild(_childBullet[i],i+1);
		Vec2 v =getContentSize();
		_childBullet[i]->setColor(Color3B(i==0?255:0,i==1?255:0,i==2?255:0));
		_childTail[i] = ParticleSystemQuad::create("effects/Particle_PointStreak.plist");
		_childTail[i]->setStartColor(Color4F(i==0?1:0,i==1?1:0,i==2?1:0,1));
		getParent()->addChild(_childTail[i]);
		_childBullet[i]->setPosition(v.x/2 + 16*cos(i* CC_DEGREES_TO_RADIANS(120)), v.y/2 + 16*sin(i* CC_DEGREES_TO_RADIANS(120)));
		_childTail[i]->setPosition(convertToWorldSpace(_childBullet[i]->getPosition()));
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(_childTail[i]);

	
	}

	RotateBy* ro = RotateBy::create(0.36,360);
	RepeatForever* rept = RepeatForever::create(ro);
	runAction(rept);

	scheduleUpdate();


	float dis = getPosition().getDistance(_target->getPosition());
	MoveTo* move = MoveTo::create(dis / 270.0 , _target->getPosition());
	ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeConsumer::explode,this));

	Sequence* sqe = Sequence::create(move,explode,NULL);

	runAction(sqe);
}


void BulletTypeConsumer::update( float delta )
{


	for (int i = 0 ; i<3 ; i++)
	{

		_childTail[i]->setPosition(convertToWorldSpace(_childBullet[i]->getPosition()));
	}




}



