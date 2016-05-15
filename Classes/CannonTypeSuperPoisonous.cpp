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
	_cover->setPosition(getContentSize()/2);

	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	dir = 18 *dir;

	auto seq1 = Sequence::create(ScaleTo::create(0.1,0.2),ScaleTo::create(0.25,1),NULL);
	auto seq2 = Sequence::create(MoveBy::create(0.1,dir),MoveBy::create(0.1,-1*dir),NULL);
	
	_cover->runAction(Spawn::create(seq1,seq2,NULL));




	BulletTypeSuperPoisonous* bullet = BulletTypeSuperPoisonous::create();
	getParent()->addChild(bullet);

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 234.5, 15.0 + 28.0 * (float)_color.r / 255 , 59);

	bullet->setTarget(_target);
	bullet->setDamageContributerID(_damageContributerID);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_superPoisonous.mp3");



}

void CannonTypeSuperPoisonous::setColorInfo( cocos2d::Color3B c3b )
{

	Cannon::setColorInfo(c3b);
	_cover->setColor(c3b);

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
	_cover->setRotation(_cover->getRotation()-1);
	return;
}



