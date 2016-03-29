#include "CannonTypePoisonousOne.h"
#include "BulletTypePoisonousOne.h"
#include "NumericalManager.h"


USING_NS_CC;
const int color_tag = 111;

bool CannonTypePoisonousOne::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	((Sprite*)(getChildByTag(color_tag)))->setScaleX(0.5);
	setTexture("cannons/CannonCover_PoisonousOne.png");



	return true;
}




void CannonTypePoisonousOne::attackOnce()
{

	BulletTypePoisonousOne* bullet = BulletTypePoisonousOne::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 0.6 , 1500);
	bullet->setDamageContributerID(_damageContributerID);


	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_poisonousOne.wav");


	isAttacking = false;
	_target = nullptr;

}

