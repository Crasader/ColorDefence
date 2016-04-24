#include "CannonTypeLargeWave.h"
#include "BulletTypeLargeWave.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeLargeWave::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_LargeWave_base.png");

	_rot = Sprite::create("cannons/CannonCover_LargeWave_rot.png");
	addChild(_rot, -1);
	_rot->setPosition(getContentSize()/2);

	return true;
}




void CannonTypeLargeWave::attackOnce()
{

	BulletTypeLargeWave* bullet = BulletTypeLargeWave::create();

	getParent()->addChild(bullet,2);

	bullet->setPosition(getPosition());
	//bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 45);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_largeWave.mp3");
	setRotation(getRotation() + 60);

	stopAllActions();
	setOpacity(0);
	auto act1 = FadeIn::create(_attackInterval/60.0);
	//auto act2 = CallFunc::create([&](){ setScale(1); });
	//auto seq = Sequence::create(act1,act2,NULL);
	runAction(act1);

}

void CannonTypeLargeWave::setDirection()
{
	_rot-> setRotation(_rot->getRotation() - 2.0);
}

void CannonTypeLargeWave::tryGetTarget()
{
	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: em->enemiesInSequence)
	{
		if ((!e->isAntiMagic())&&(getPosition().getDistance(e->getPosition())<=attackRange))
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
		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_target->getPosition()))
		{
			_target = e;
			isAttacking = true;
		}
	}



}


