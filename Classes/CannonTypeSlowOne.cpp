#include "CannonTypeSlowOne.h"
#include "BulletTypeSlowOne.h"
#include "NumericalManager.h"


USING_NS_CC;

bool CannonTypeSlowOne::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_SlowOne.png");



	return true;
}




void CannonTypeSlowOne::attackOnce()
{

	BulletTypeSlowOne* bullet = BulletTypeSlowOne::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 0.45 , 500);



	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_slowOne.wav");



	isAttacking = false;
	_target = nullptr;


}

