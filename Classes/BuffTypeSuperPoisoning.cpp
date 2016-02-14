#include "BuffTypeSuperPoisoning.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BuffTypeSuperPoisoning::init(Enemy* enemy, float poisonousDamage ,float poisonousTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeSuperPoisoning;
	//_buffType = 4;


	//_target = enemy;
	_poisonousDamage = poisonousDamage;
	_buffTimeRest = poisonousTime;


	return true;
}

void BuffTypeSuperPoisoning::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);

 	if (_buffTimeRest > 0)
 	{
 		target->onMagicalDamaged(_poisonousDamage);
 	}

 	
	

}

BuffTypeSuperPoisoning* BuffTypeSuperPoisoning::create(Enemy* enemy, float poisonousDamage ,float poisonousTime)
{

	BuffTypeSuperPoisoning *pRet = new BuffTypeSuperPoisoning(); 
	if (pRet && pRet->init( enemy, poisonousDamage ,poisonousTime)) 
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

void BuffTypeSuperPoisoning::overrideWithNewBuff( Buff* newBuff )
{

	_poisonousDamage = _poisonousDamage>((BuffTypeSuperPoisoning*)newBuff)->_poisonousDamage?_poisonousDamage:((BuffTypeSuperPoisoning*)newBuff)->_poisonousDamage;

	_buffTimeRest = _buffTimeRest>((BuffTypeSuperPoisoning*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeSuperPoisoning*)newBuff)->_buffTimeRest;
}

void BuffTypeSuperPoisoning::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{

		target->setSuperPoisoningState(true);

		SoundManager::getInstance()->playSoundEffect("sound/buff_poisonous.wav");

		ParticleSystem* slow_buff = ParticleSystemQuad::create("effects/Particle_SuperPoisonous.plist");
		slow_buff->setPosition(getContentSize().width/2,getContentSize().height/2);
		target->addChild(slow_buff,10,_buffType);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(slow_buff);
	}
	else
	{

		target->setSuperPoisoningState(false);

		if (target->getChildByTag(_buffType)!= nullptr)
		{

			((ParticleSystem*)(target->getChildByTag(_buffType)))->setEmissionRate(0);
			ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(((ParticleSystem*)(target->getChildByTag(_buffType))));
			ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(((ParticleSystem*)(target->getChildByTag(_buffType))));
			target->removeChildByTag(_buffType);

		}
	}
}

bool BuffTypeSuperPoisoning::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	if ((target->hasBuffPoisoning())||(target->hasBuffPoisoning()))
	{
		return true;
	}
	return false;
}
