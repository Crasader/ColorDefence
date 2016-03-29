#include "EnemyTypeSeparator.h"


USING_NS_CC;

bool EnemyTypeSeparator::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}

	_enemyType = 0;



	timeInterval = 400;
	isRealEnemy = false;


	return true;
}






