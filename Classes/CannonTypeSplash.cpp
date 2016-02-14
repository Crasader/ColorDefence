#include "CannonTypeSplash.h"
#include "BulletTypeSplash.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeSplash::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Splash.png");


	return true;
}




void CannonTypeSplash::attackOnce()
{



	BulletTypeSplash* bullet = BulletTypeSplash::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 88);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_splash.wav");



}

