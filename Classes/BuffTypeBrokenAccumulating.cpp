#include "BuffTypeBrokenAccumulating.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BuffTypeBrokenAccumulating::init(Enemy* enemy, float brokenValue ,float brokenTime)
{

	if ( !BuffTypeBroken::init( enemy, brokenValue ,brokenTime) )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeBroken;
	//_buffType = 2;


	//_target = enemy;
	_brokenValue = brokenValue;
	_buffTimeRest = brokenTime;


	return true;
}



BuffTypeBrokenAccumulating* BuffTypeBrokenAccumulating::create(Enemy* enemy, float brokenValue ,float brokenTime)
{

	BuffTypeBrokenAccumulating *pRet = new BuffTypeBrokenAccumulating(); 
	if (pRet && pRet->init(enemy,  brokenValue , brokenTime)) 
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

void BuffTypeBrokenAccumulating::overrideWithNewBuff( Buff* newBuff )
{

// 	_brokenValue = _brokenValue + ((BuffTypeBroken*)newBuff)->_brokenValue;
// 
// 	_buffTimeRest = _buffTimeRest>(static_cast<BuffTypeBroken*>(newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeBroken*)newBuff)->_buffTimeRest;

}

