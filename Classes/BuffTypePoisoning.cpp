#include "BuffTypePoisoning.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"
#include "DamageContributionManager.h"

USING_NS_CC;

bool BuffTypePoisoning::init(Enemy* enemy, float poisonousDamage ,float poisonousTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypePoisoning;
	//_buffType = 1;


	//_target = enemy;
	_poisonousDamage = poisonousDamage;
	_buffTimeRest = poisonousTime;


	return true;
}

void BuffTypePoisoning::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);

 	if (_buffTimeRest > 0)
 	{
 		float damageContributed = target->onMagicalDamaged(_poisonousDamage);
		DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
 	}

 	
	

}

BuffTypePoisoning* BuffTypePoisoning::create(Enemy* enemy, float poisonousDamage ,float poisonousTime)
{

	BuffTypePoisoning *pRet = new BuffTypePoisoning(); 
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

void BuffTypePoisoning::overrideWithNewBuff( Buff* newBuff )
{

	_poisonousDamage = _poisonousDamage>((BuffTypePoisoning*)newBuff)->_poisonousDamage?_poisonousDamage:((BuffTypePoisoning*)newBuff)->_poisonousDamage;

	_buffTimeRest = _buffTimeRest>((BuffTypePoisoning*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypePoisoning*)newBuff)->_buffTimeRest;


	_damageContributerID = ((BuffTypePoisoning*)newBuff)->_damageContributerID;
}

void BuffTypePoisoning::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{

		target->setPoisoningState(true);

		SoundManager::getInstance()->playSoundEffect("sound/buff_poisonous.mp3");

		ParticleSystem* slow_buff = ParticleSystemQuad::create("effects/Particle_Poisonous.plist");
		slow_buff->setPosition(getContentSize().width/2,getContentSize().height/2);
		addChild(slow_buff,10,_buffType);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(slow_buff);
	}
	else
	{

		target->setPoisoningState(false);

		if (getChildByTag(_buffType)!= nullptr)
		{

			((ParticleSystem*)(getChildByTag(_buffType)))->setEmissionRate(0);
			ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(((ParticleSystem*)(getChildByTag(_buffType))));
			ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(((ParticleSystem*)(getChildByTag(_buffType))));
			removeChildByTag(_buffType);

		}
	}
}

bool BuffTypePoisoning::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	if (target->isAntiMagic())
	{
		return false;
	}

	if (target->hasBuffSuperPoisoning())
	{
		return false;
	}
	return true;
}
