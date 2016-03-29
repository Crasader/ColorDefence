#include "CannonTypeArmorRemover.h"
#include "BulletTypeArmorRemover.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeArmorRemover::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_ArmorRemover_part1.png");

	_cover = Sprite::create("cannons/CannonCover_ArmorRemover_part2.png");
	addChild(_cover);
	_cover->setPosition(getContentSize()/2);


	return true;
}




void CannonTypeArmorRemover::attackOnce()
{



	BulletTypeArmorRemover* bullet = BulletTypeArmorRemover::create();
	getParent()->addChild(bullet);
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange ,8 , 200);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//


	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_armorRemover.mp3");


}

void CannonTypeArmorRemover::setDirection()
{
	setRotation(getRotation()-1);
	_cover->setRotation(getRotation()+3);
	return;
}

