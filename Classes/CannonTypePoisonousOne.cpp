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
	setTexture("cannons/CannonCover_PoisonousOne_base.png");

	_piston = Sprite::create("cannons/CannonCover_PoisonousOne_piston.png");
	//_piston = Sprite::create();
	this->addChild(_piston);
	_piston->setPosition(getContentSize()/2);


	//_canRotate = true;

	return true;
}




void CannonTypePoisonousOne::attackOnce()
{

	//_canRotate = false;

	BulletTypePoisonousOne* bullet = BulletTypePoisonousOne::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 36.0 , 25.0);
	bullet->setDamageContributerID(_damageContributerID);


	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_poisonousOne.wav");

	_piston->stopAllActions();
	_piston->setPosition((Vec2)(getContentSize()/2)+Vec2(0,-8));
	auto mv1 = MoveBy::create(0.1,Vec2(0,16));
	auto mv2 = MoveTo::create(0.1,getContentSize()/2);
	_piston->runAction(Sequence::create(mv1,mv2,NULL));


	isAttacking = false;
	_target = nullptr;





}

void CannonTypePoisonousOne::setDirection()
{
	//if (_canRotate)
	//{
		Cannon::setDirection();
	//}
	

}

void CannonTypePoisonousOne::pause()
{
	_piston->pause();
	Sprite::pause();
}

void CannonTypePoisonousOne::resume()
{
	Sprite::resume();
	_piston->resume();
}