#include "BulletTypeChains.h"
#include "BulletManager.h"
#include "BuffTypeStun.h"

USING_NS_CC;

bool BulletTypeChains::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}



	//BulletManager::getInstance()->bullets.pushBack(this);



	return true;
}



void BulletTypeChains::explode()
{
	

	_target->onPhysicalDamaged(_damage);
	//_target->setBuffStun(_stunTime);
	_target->setBuff(BuffTypeStun::create(_target,_stunTime));
	
	//¶¯»­

	auto ex1 = DelayTime::create(_stunTime/60);
	auto ex2 = FadeOut::create(0.12);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex1,ex2,ex4,nullptr));



}

void BulletTypeChains::setTarget( Enemy* enemy )
{

	_target = enemy;

	float cLength = getPosition().getDistance(_target->getPosition());
	Point center = 0.5*(getPosition() + _target->getPosition());
	Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
	
	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,2,1));
	setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);

	auto st = ScaleTo::create(0.08,1,cLength);
	auto mt = MoveTo::create(0.08,center);
	auto sp = Spawn::create(st,mt,nullptr);
	auto ex = CallFunc::create([&]{
		explode();
	});
	auto sq = Sequence::create(sp,ex,nullptr);
	
	runAction(sq);



}

void BulletTypeChains::setDamage( float dmg , float stunTime )
{
	_damage = dmg;
	_stunTime = stunTime;
}



