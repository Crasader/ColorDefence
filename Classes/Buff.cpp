#include "Buff.h"
#include "Enemy.h"

USING_NS_CC;


bool Buff::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}

	_buffType = 0;

	_buffTimeRest = 10;

	_end = false;

	//retain();

	return true;
}

void Buff::makeEffectWithTarget(Enemy* target)
{
	_buffTimeRest -- ;

 	if (_buffTimeRest <= 0)
 	{

 		//release();
		_end = true;
 	}
}

void Buff::overrideWithNewBuff( Buff* newBuff )
{

}

bool Buff::willEndBuff()
{

	return _end;
}

unsigned Buff::getBuffType()
{
	return _buffType;
}


bool Buff::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	if (target->isAntiMagic())
	{
		return false;
	}
	return true;
}

void Buff::setAppearacneWithTarget( Enemy* target , bool show )
{

}











