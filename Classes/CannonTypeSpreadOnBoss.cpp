#include "CannonTypeSpreadOnBoss.h"
#include "BulletTypeSpreadOnBoss.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeSpreadOnBoss::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_SpreadOnBoss.png");


	return true;
}




void CannonTypeSpreadOnBoss::attackOnce()
{



	BulletTypeSpreadOnBoss* bullet = BulletTypeSpreadOnBoss::create();
	
	getParent()->addChild(bullet);
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage);

	bullet->setTarget(_target);
	bullet->setDamageContributerID(_damageContributerID);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_splash.wav");



}

void CannonTypeSpreadOnBoss::tryGetTarget()
{


	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: em->enemiesInSequence)
	{
		if ((e->isBoss())&&(getPosition().getDistance(e->getPosition())<=attackRange))
		{
			v_target.pushBack(e);
		}
	}


	if (v_target.empty())
	{
		Cannon::tryGetTarget();
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
