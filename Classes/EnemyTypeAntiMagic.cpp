#include "EnemyTypeAntiMagic.h"




USING_NS_CC;

bool EnemyTypeAntiMagic::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}

	getEquipment()->setTexture("enemies/type_antiMagic_01.png");
	getEquipment()->setPosition(getAppearance()->getContentSize()/2);
	//enemy->getEquipment()->removeFromParent();
	//enemy->addChild(enemy->getEquipment());
	RotateBy* ro =  RotateBy::create(8,-360);
	getEquipment()->runAction(RepeatForever::create(ro));
	auto inner = Sprite::create("enemies/type_antiMagic_01_inner.png");
	getEquipment()->addChild(inner,2);
	inner->setPosition(getEquipment()->getContentSize()/2);
	RotateBy* roi =  RotateBy::create(1,360);
	inner->runAction(RepeatForever::create(roi));
	//enemy->getEquipment()->setPosition(0,0);


	return true;
}



void EnemyTypeAntiMagic::setEnemyParameter(int hp, float ms, float arm )
{



	_moveSpeedFull = ms;
	moveSpeed = _moveSpeedFull;

	//_armorFull = arm;
	_armorFull = 0;
	_armor = _armorFull;

	_fullHitPoint = hp;
	_hitPoint = _fullHitPoint;



}

bool EnemyTypeAntiMagic::isAntiMagic()
{
	return true;
}




