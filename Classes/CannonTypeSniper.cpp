#include "CannonTypeSniper.h"
#include "BulletTypeSniper.h"
#include "NumericalManager.h"

USING_NS_CC;
const int color_tag = 111;



bool CannonTypeSniper::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Sniper_base.png");

	((Sprite*)getChildByTag(color_tag))->setScale(0.7);

	_barrel = Sprite::create("cannons/CannonCover_Sniper_barrel.png");
	addChild(_barrel);
	_barrel->setPosition(getContentSize()/2);

	//hasMoved = false;

	return true;
}




void CannonTypeSniper::attackOnce()
{

	/*
	if (!hasMoved)
	{
		//originalPosition = getPosition();
		hasMoved = true;
	}
	*/


	_barrel->stopAllActions();
	_barrel->setPosition(getContentSize()/2);


	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	dir = -20 *dir;

	auto mb1 = MoveBy::create(0.02,dir);
	auto mb2 = MoveBy::create(0.18,dir*(-1));
	_barrel->runAction(Sequence::create(mb1,mb2,nullptr));


	BulletTypeSniper* bullet = BulletTypeSniper::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(_barrel->getRotation());



	getParent()->addChild(bullet);
	bullet->setTarget(_target);
	bullet->setDamage(_damage);


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//


	isAttacking = false;
	_target = nullptr;

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_sniper.mp3");

}

void CannonTypeSniper::tryGetTarget()
{
	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: em->enemiesInSequence)
	{
		if (getPosition().getDistance(e->getPosition())<=attackRange)
		{
			v_target.pushBack(e);
		}
	}


	if (v_target.empty())
	{
		return;
	}

	_target = v_target.front();

	for (Enemy*e : v_target)
	{
		if (e->getMovingProgress()>_target->getMovingProgress())
		{
			_target = e;
			
		}
	}
	isAttacking = true;

}

void CannonTypeSniper::setDirection()
{
	if ((_barrel->getPosition().getDistance(getContentSize()/2) > 3 )/*&&(hasMoved)*/)
	{
		return;
	}
	Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
	_barrel->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
}

void CannonTypeSniper::pause()
{
	_barrel->pause();
	Sprite::pause();
}

void CannonTypeSniper::resume()
{
	Sprite::resume();
	_barrel->resume();
}

