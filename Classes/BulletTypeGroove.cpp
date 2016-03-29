#include "BulletTypeGroove.h"
#include "BulletManager.h"
#include "BuffTypeStun.h"
#include "EnemyManager.h"

USING_NS_CC;

bool BulletTypeGroove::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}



	setTexture("effects/Bullet_Groove.png");

	setScale(0.1,0.01);



	return true;
}



void BulletTypeGroove::explode()
{

	//到沟壑距离足够的怪 都会受到伤害 加buff晕
	EnemyManager* em = EnemyManager::getInstance();

	for (Enemy* e:em->enemiesInSequence)
	{

		if (((abs(ccpCross((e->getPosition() - _end[0]),(e->getPosition() - _end[1])))/_grooveLength) <18 )&&(ccpDistance(e->getPosition(),0.5*(_end[0]+_end[1]))< _grooveLength/2 + 18))
		{
			float damageContributed = e->onPhysicalDamaged(_damage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
			e->setBuff(BuffTypeStun::create(e,_stunTime));
			_blocked.pushBack(e);
		}

	}

	


	//碰到沟壑的怪也会被晕
	scheduleUpdate();





}

void BulletTypeGroove::setTarget( Enemy* enemy )
{

	_target = enemy;

	_end[0] = getPosition();
	_end[1] = _target->getPosition();

	Vec2 normalized = ccpNormalize(ccp(_end[1].x - _end[0].x,	_end[1].y - _end[0].y));

	_end[1] = _end[0] + normalized * _grooveLength ;

	Point center = 0.5*(_end[0] + _end[1]);


	//Vec2 normalized = ccpNormalize(ccp(_end[1].x - _end[0].x,	_end[1].y - _end[0].y));
	setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
	float ratio = _grooveLength/180.0 ;

	auto st = ScaleTo::create(0.08,1,ratio);
	auto mt = MoveTo::create(0.08,center);
	auto sp = Spawn::create(st,mt,nullptr);
	auto ex = CallFunc::create([&]{
		explode();
	});
	auto sq = Sequence::create(sp,ex,nullptr);

	runAction(sq);



}

void BulletTypeGroove::setDamage( float dmg , float stunTime  ,float grooveLength)
{
	_damage = dmg;
	_stunTime = stunTime;
	_grooveLength = grooveLength;
}

void BulletTypeGroove::update( float delta )
{
	_stunTime --;
	if (_stunTime<= 0)
	{
		unscheduleUpdate();
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
		return;
	}


	//碰到沟壑的怪 晕了
	EnemyManager* em = EnemyManager::getInstance();
	for (Enemy* e:em->enemiesInSequence)
	{

		if(!_blocked.contains(e))
		{
			if (((abs(ccpCross((e->getPosition() - _end[0]),(e->getPosition() - _end[1])))/_grooveLength) <18 )&&(ccpDistance(e->getPosition(),0.5*(_end[0]+_end[1]))< _grooveLength/2 + 18))
			{
				e->setBuff(BuffTypeStun::create(e,_stunTime));
				_blocked.pushBack(e);
			}
		}



	}



}



