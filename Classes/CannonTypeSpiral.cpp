#include "CannonTypeSpiral.h"
#include "BulletTypeSpiral.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeSpiral::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Spiral.png");
	setOpacity(0);
	

	_inner = Sprite::create("cannons/CannonCover_Spiral_inner.png");
	addChild(_inner,3);
	_inner->setPosition(getContentSize()/2);

	_outter = Sprite::create("cannons/CannonCover_Spiral_outter.png");
	addChild(_outter,3);
	_outter->setPosition(getContentSize()/2);
	_outter->setOpacity(150);



	hasExtraState = true;
	extraStateOn = false;

	return true;
}




void CannonTypeSpiral::attackOnce()
{



	BulletTypeSpiral* bullet = BulletTypeSpiral::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//


	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_shadow.mp3");


}

void CannonTypeSpiral::setDirection()
{

	_inner->setRotation(_inner->getRotation()+(extraStateOn?12:-6));
	_outter->setRotation(_outter->getRotation()+(extraStateOn?-2:1));

}

void CannonTypeSpiral::setExtraState( bool on )
{

	Cannon::setExtraState(on);

	_outter->setOpacity(on?255:150);

}

