#include "BuffTypeStun.h"
#include "Enemy.h"


USING_NS_CC;

bool BuffTypeStun::init(Enemy* enemy, float stunTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeStun;
	//_buffType = 3;


	_buffTimeRest = stunTime;

	return true;
}

void BuffTypeStun::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);
	
}

BuffTypeStun* BuffTypeStun::create(Enemy* enemy, float stunTime)
{

	BuffTypeStun *pRet = new BuffTypeStun(); 
	if (pRet && pRet->init( enemy, stunTime)) 
	{
		pRet->autorelease(); 
		return pRet; 
	}
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 

}

void BuffTypeStun::overrideWithNewBuff( Buff* newBuff )
{

	_buffTimeRest = _buffTimeRest>((BuffTypeStun*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeStun*)newBuff)->_buffTimeRest;
}



bool BuffTypeStun::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	return true;
}

void BuffTypeStun::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{
		target->setStun(true);
	}
	else
	{
		target->setStun(false);
	}
}
