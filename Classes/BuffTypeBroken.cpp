#include "BuffTypeBroken.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BuffTypeBroken::init(Enemy* enemy, float brokenValue ,float brokenTime)
{

	if ( !Buff::init() )
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

void BuffTypeBroken::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);

 	if (_buffTimeRest <= 0)
 	{
 		target->setArmorLose(0);
 	}
 	else
 	{
 		target->setArmorLose(_brokenValue);
 	}
 	
	

}

BuffTypeBroken* BuffTypeBroken::create(Enemy* enemy, float brokenValue ,float brokenTime)
{

	BuffTypeBroken *pRet = new BuffTypeBroken(); 
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

void BuffTypeBroken::overrideWithNewBuff( Buff* newBuff )
{

	_brokenValue = _brokenValue>((BuffTypeBroken*)newBuff)->_brokenValue?_brokenValue:((BuffTypeBroken*)newBuff)->_brokenValue;

	_buffTimeRest = _buffTimeRest>((BuffTypeBroken*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeBroken*)newBuff)->_buffTimeRest;
}

void BuffTypeBroken::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{
		SoundManager::getInstance()->playSoundEffect("sound/buff_broken.wav");

		auto fi = FadeIn::create(0.5);
		auto fo = FadeOut::create(0.5);
		auto rep = RepeatForever::create(Sequence::create(fi,fo,nullptr));
		target->getEquipment()->runAction(rep);
	}
	else
	{
		target->getEquipment()->stopAllActions();
		target->getEquipment()->setOpacity(255);
	}
}

bool BuffTypeBroken::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	if (target->hasArmor())
	{
		return true;
	}
	return false;
}
