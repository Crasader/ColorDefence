#include "EnemyTypeSeparator.h"


USING_NS_CC;

bool EnemyTypeSeparator::init()
{

	if ( !Enemy::init() )
	{
		return false;
	}

	_enemyType = 0;



	timeInterval = 6.6f;
	isRealEnemy = false;


	return true;
}






