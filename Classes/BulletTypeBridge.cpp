#include "BulletTypeBridge.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeBridge::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Bridge.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_damageRadius = 1;
	_bridging = false;

	return true;
}



void BulletTypeBridge::explode()
{

	if (_bridging)
	{

		if (_target == nullptr)
		{
			BulletManager::getInstance()->bullets.eraseObject(this);
			removeFromParent();
			return;
		}
		EnemyManager* em  = EnemyManager::getInstance();
		Point pt = _target->getPosition();
		for (Enemy* e : em->enemiesInSequence)
		{
			if (pt.getDistance(e->getPosition())<_damageRadius)
			{
				float damageContributed = e->onPhysicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			}
		}
		unscheduleUpdate();


		//¶¯»­

		auto ex1 = FadeOut::create(0.5);
		auto ex2 = ScaleTo::create(0.3f,4);
		auto ex3 = Spawn::create(ex1,ex2,nullptr);

		auto ex4 = CallFunc::create([&]{
			BulletManager::getInstance()->bullets.eraseObject(this);
			removeFromParent();
		});

		runAction(Sequence::create(ex3,ex4,NULL));

		SoundManager::getInstance()->playSoundEffect("sound/bullet_explode_brige_bridging.mp3");

	}
	else
	{
		float damageContributed = _target->onPhysicalDamaged(_damage);
		DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	}




}

void BulletTypeBridge::setDamage( float damage, bool bridging, float damageRadius)
{
	_damage = damage;
	_bridging = bridging;
	_damageRadius = damageRadius;

}

void BulletTypeBridge::setTarget( Cannon* cannon )
{


	_targetCannon = cannon;
	Point targetLocation = _targetCannon->getPosition();

	float dis = targetLocation.getDistance(getPosition());

	MoveTo* move = MoveTo::create(0.0003*dis, targetLocation);
	ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeBridge::bridge,this));

	Sequence* sqe = Sequence::create(move,explode,NULL);

	runAction(sqe);
}

void BulletTypeBridge::setTarget( Enemy* enemy )
{
	_target = enemy;

	if (_bridging)
	{
		scheduleUpdate();
	}
	else
	{
		float dis = _target->getPosition().getDistance(getPosition());
		MoveTo* move = MoveTo::create(0.2f , _target->getPosition());
		ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeBridge::explode,this));

		Sequence* sqe = Sequence::create(move,explode,NULL);

		runAction(sqe);
	}


}

void BulletTypeBridge::bridge()
{

	SoundManager::getInstance()->playSoundEffect("sound/cannon_bridge.wav");

	Vector<Enemy*> eis = EnemyManager::getInstance()->enemiesInSequence;

	runAction(RepeatForever::create(RotateBy::create(1,1800)));

	if (eis.empty())
	{

		_target = nullptr;
		explode();
		return;
	}


	_target = eis.front();

	for (Enemy*e : eis)
	{
		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_target->getPosition()))
		{
			_target = e;
		}
	}

	setTarget(_target);

}

void BulletTypeBridge::update( float delta )
{
	if ((_target->isFloating)||(!_target->isAlive()))
	{
		_target = nullptr;
		explode();
		return;
	}



	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	//setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	dir = 12*dir;
	setPosition(getPosition()+dir);


	if (getPosition().getDistance(_target->getPosition())<20)
	{
		explode();
	}
}


