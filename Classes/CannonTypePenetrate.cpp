#include "CannonTypePenetrate.h"
#include "BulletTypePenetrate.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypePenetrate::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Penetrate.png");


	return true;
}




void CannonTypePenetrate::attackOnce()
{

	BulletTypePenetrate* bullet = BulletTypePenetrate::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 45);
	bullet->setDamageContributerID(_damageContributerID);


	bullet->setTarget(_target);
	getParent()->addChild(bullet);


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_penetrate.wav");

}

