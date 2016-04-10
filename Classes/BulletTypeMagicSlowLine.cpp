#include "BulletTypeMagicSlowLine.h"
#include "BulletManager.h"
#include "BuffTypeSlow.h"


USING_NS_CC;

bool BulletTypeMagicSlowLine::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_MagicSlowLine.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	em = EnemyManager::getInstance();
	enemiesDamaged = Vector<Enemy*>();

	_damageWidth = 90;
	_slowFactor = 1;
	_slowTime = 1;

	return true;
}


void BulletTypeMagicSlowLine::setTarget( Enemy* enemy )
{

	Vec2 v = Vec2(enemy->getPosition()- getPosition());
	v.normalize();
	v = v* 1500;
	
	auto mv = MoveBy::create(2,v);
	auto expld = CallFunc::create([&]{
		
		explode();

	});

	scheduleUpdate();
	runAction(Sequence::create(mv,expld,NULL));


}

void BulletTypeMagicSlowLine::explode()
{

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}

void BulletTypeMagicSlowLine::setDamage(float damage , float damageWidth, float slowFactor , float slowTime)
{
	_damage = damage;
	_damageWidth = damageWidth;
	_slowFactor = slowFactor;
	_slowTime = slowTime;
}



void BulletTypeMagicSlowLine::update( float delta )
{
	for (Enemy* e : em->enemiesInSequence)
	{
		if (!enemiesDamaged.contains(e))
		{
			if (getPosition().getDistance(e->getPosition())<_damageWidth)
			{
				enemiesDamaged.pushBack(e);
				float damageContributed = e->onMagicalDamaged(_damage);
				DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
				auto buff = BuffTypeSlow::create(e , _slowFactor,_slowTime);
				//buff->setDamageContributerID(_damageContributerID);
				e->setBuff(buff);

			}
		}

	}
}






