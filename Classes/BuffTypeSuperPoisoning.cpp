#include "BuffTypeSuperPoisoning.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"
#include "DamageContributionManager.h"

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
		float damageContributed = target->onMagicalDamaged(_poisonousDamage);
		DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
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


	_damageContributerID = ((BuffTypeSuperPoisoning*)newBuff)->_damageContributerID;
}

void BuffTypeSuperPoisoning::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{

		target->setSuperPoisoningState(true);

		SoundManager::getInstance()->playSoundEffect("sound/buff_poisonous.wav");

		ParticleSystem* slow_buff = ParticleSystemQuad::create("effects/Particle_SuperPoisonous.plist");
		slow_buff->setPosition(getContentSize().width/2,getContentSize().height/2);
		addChild(slow_buff,10,_buffType);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(slow_buff);
	}
	else
	{

		target->setSuperPoisoningState(false);

		if (getChildByTag(_buffType)!= nullptr)
		{

			((ParticleSystem*)(getChildByTag(_buffType)))->setEmissionRate(0);
			ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(((ParticleSystem*)(getChildByTag(_buffType))));
			ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(((ParticleSystem*)(getChildByTag(_buffType))));
			removeChildByTag(_buffType);

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
