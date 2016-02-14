#include "EnemyTypeBoss.h"



USING_NS_CC;

bool EnemyTypeBoss::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}


	_chancesCost = 2;

	getEquipment()->setTexture("enemies/type_boss_01.png");
	getEquipment()->setPosition(getAppearance()->getContentSize()/2);
	auto light = Sprite::create("enemies/type_boss_01_light.png");
	getEquipment()->addChild(light,2);
	light->setPosition(getEquipment()->getContentSize()/2);
	FadeIn* fi = FadeIn::create(0.6);
	FadeOut* fo = FadeOut::create(0.6);
	Sequence* sq = Sequence::create(fi,fo,nullptr);
	light->runAction(RepeatForever::create(sq));


	return true;
}



void EnemyTypeBoss::setEnemyParameter(int hp, float ms, float arm )
{



	_moveSpeedFull = ms * 0.5;
	moveSpeed = _moveSpeedFull;

	_armorFull = arm * 0.1;
	_armor = _armorFull;

	_fullHitPoint = hp*10;
	_hitPoint = _fullHitPoint;



}

bool EnemyTypeBoss::isBoss()
{
	return true;
}






