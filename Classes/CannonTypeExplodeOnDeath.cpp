#include "CannonTypeExplodeOnDeath.h"
#include "BulletTypeExplodeOnDeath.h"
#include "NumericalManager.h"


USING_NS_CC;

bool CannonTypeExplodeOnDeath::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_ExplodeOnDeath.png");



	return true;
}




void CannonTypeExplodeOnDeath::attackOnce()
{

	BulletTypeExplodeOnDeath* bullet = BulletTypeExplodeOnDeath::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 290 , 255);
	bullet->setDamageContributerID(_damageContributerID);


	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_eod.mp3");



	isAttacking = false;
	_target = nullptr;


}

