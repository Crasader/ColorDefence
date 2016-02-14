#include "CannonTypeSuperPoisonous.h"
#include "BulletTypeSuperPoisonous.h"
#include "NumericalManager.h"

USING_NS_CC;
const int color_tag = 111;

bool CannonTypeSuperPoisonous::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_SuperPoisonous_base.png");


	_cover = Sprite::create("cannons/CannonCover_SuperPoisonous_cover.png");
	addChild(_cover);
	_cover->setPosition(getContentSize()/2);

	return true;
}




void CannonTypeSuperPoisonous::attackOnce()
{

	_cover->stopAllActions();
	_cover->setScale(1);
	_cover->runAction(Sequence::create(ScaleTo::create(0.1,0.2),ScaleTo::create(0.25,1),NULL));




	BulletTypeSuperPoisonous* bullet = BulletTypeSuperPoisonous::create();
	getParent()->addChild(bullet);

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 4.2, 880 , 45);

	bullet->setTarget(_target);
	

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_splash.wav");



}

void CannonTypeSuperPoisonous::setColorInfo( cocos2d::Color3B c3b )
{

	(this->getChildByTag(color_tag))->setColor(c3b);
	_cover->setColor(c3b);

	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);

}

void CannonTypeSuperPoisonous::pause()
{
	Cannon::pause();
	_cover->pause();
}

void CannonTypeSuperPoisonous::resume()
{
	Cannon::resume();
	_cover->resume();
}

void CannonTypeSuperPoisonous::setDirection()
{
	setRotation(getRotation()-3);
	return;
}



