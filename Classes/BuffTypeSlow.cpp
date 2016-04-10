#include "BuffTypeSlow.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BuffTypeSlow::init(Enemy* enemy, float slowFactor ,float slowTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeSlow;
	//_buffType = 0;


	//_target = enemy;
	_slowFactor = slowFactor;
	_buffTimeRest = slowTime;


	return true;
}

void BuffTypeSlow::makeEffectWithTarget(Enemy* target, float delta)
{

	Buff::makeEffectWithTarget(target,delta);

 	if (_buffTimeRest <= 0)
 	{
 		target->setSpeedFactor(1.0);
 	}
 	else
 	{
 		target->setSpeedFactor(_slowFactor);
 	}
 	
	

}

BuffTypeSlow* BuffTypeSlow::create(Enemy* enemy, float slowFactor ,float slowTime)
{

	BuffTypeSlow *pRet = new BuffTypeSlow(); 
	if (pRet && pRet->init( enemy, slowFactor ,slowTime)) 
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

void BuffTypeSlow::overrideWithNewBuff( Buff* newBuff )
{

	_slowFactor = _slowFactor>((BuffTypeSlow*)newBuff)->_slowFactor?_slowFactor:((BuffTypeSlow*)newBuff)->_slowFactor;

	_buffTimeRest = _buffTimeRest>((BuffTypeSlow*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeSlow*)newBuff)->_buffTimeRest;
}

void BuffTypeSlow::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{
		SoundManager::getInstance()->playSoundEffect("sound/buff_slow.wav");

		ParticleSystem* slow_buff = ParticleSystemQuad::create("effects/Particle_Slow.plist");
		slow_buff->setPosition(getContentSize().width/2,getContentSize().height/2);
		//target->addChild(slow_buff,10,_buffType);
		addChild(slow_buff,10,_buffType);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(slow_buff);
	}
	else
	{
		if (getChildByTag(_buffType)!= nullptr)
		{

			((ParticleSystem*)(getChildByTag(_buffType)))->setEmissionRate(0);
			ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(((ParticleSystem*)(getChildByTag(_buffType))));
			ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(((ParticleSystem*)(getChildByTag(_buffType))));

		}
	}
}
