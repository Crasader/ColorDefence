#include "CannonTypePoisonousMulti.h"
#include "BulletTypePoisonousMulti.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypePoisonousMulti::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_PoisonousMulti.png");

	_canRotate = true;



	return true;
}




void CannonTypePoisonousMulti::attackOnce()
{

	_canRotate = false;

	BulletTypePoisonousMulti* bullet = BulletTypePoisonousMulti::create();
	getParent()->addChild(bullet);

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange,0.9,1600);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_splash.wav");

	DelayTime* dt = DelayTime::create(0.8);
	CallFunc* cf = CallFunc::create([&](){

		_canRotate = true;

	});
	Sequence* seq = Sequence::create(dt,cf,NULL);
	runAction(seq);

	
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_poisonousMulti.mp3");


	isAttacking = false;
	_target = nullptr;


}

void CannonTypePoisonousMulti::setDirection()
{
	if (_canRotate)
	{
		Cannon::setDirection();
	}
}

