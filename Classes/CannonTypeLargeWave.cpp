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
	setTexture("cannons/CannonCover_LargeWave.png");


	return true;
}




void CannonTypeLargeWave::attackOnce()
{

	BulletTypeLargeWave* bullet = BulletTypeLargeWave::create();

	getParent()->addChild(bullet);

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 45);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_penetrate.wav");

}

