#include "EnemyTypeArmor.h"



USING_NS_CC;

bool EnemyTypeArmor::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}

	getEquipment()->setTexture("enemies/type_armor_01.png");
	getEquipment()->setPosition(getAppearance()->getContentSize()/2);

	return true;
}



void EnemyTypeArmor::setEnemyParameter(int hp, float ms, float arm )
{


	_moveSpeedFull = ms;
	moveSpeed = _moveSpeedFull;

	_armorFull = arm;
	_armor = _armorFull;

	_fullHitPoint = hp;
	_hitPoint = _fullHitPoint;



}

bool EnemyTypeArmor::hasArmor()
{
	return true;
}




