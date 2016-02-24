#include "BuffTypeExplodeOnDeath.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DamageContributionManager.h"


USING_NS_CC;

bool BuffTypeExplodeOnDeath::init(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeExplodeOnDeath;
	//_buffType = 6;


	_explodeRadius = explodeRadius;
	_explodeDamage = explodeDamage;
	_buffTimeRest = buffTime;

	return true;
}

void BuffTypeExplodeOnDeath::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);
	
}

BuffTypeExplodeOnDeath* BuffTypeExplodeOnDeath::create(Enemy* enemy, float explodeRadius , float explodeDamage, float buffTime)
{

	BuffTypeExplodeOnDeath *pRet = new BuffTypeExplodeOnDeath(); 
	if (pRet && pRet->init(enemy, explodeRadius , explodeDamage, buffTime)) 
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

void BuffTypeExplodeOnDeath::overrideWithNewBuff( Buff* newBuff )
{

	_explodeRadius = _explodeRadius>((BuffTypeExplodeOnDeath*)newBuff)->_explodeRadius?_explodeRadius:((BuffTypeExplodeOnDeath*)newBuff)->_explodeRadius;
	_explodeDamage = _explodeDamage>((BuffTypeExplodeOnDeath*)newBuff)->_explodeDamage?_explodeDamage:((BuffTypeExplodeOnDeath*)newBuff)->_explodeDamage;
	_buffTimeRest = _buffTimeRest>((BuffTypeExplodeOnDeath*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeExplodeOnDeath*)newBuff)->_buffTimeRest;

}



bool BuffTypeExplodeOnDeath::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}


	return true;
}

void BuffTypeExplodeOnDeath::setAppearacneWithTarget( Enemy* target , bool show )
{


	if (show)
	{
		target->setBuffExplodeOnDeathState(true);
	}
	else
	{
		target->setBuffExplodeOnDeathState(false);
	}
}

void BuffTypeExplodeOnDeath::explodeOnDeath(Point position)
{
	//Point p = ((Sprite*)(event->getUserData()))->getPosition();
	auto enemyManager = EnemyManager::getInstance();
	for (Enemy* e : enemyManager->enemiesInSequence)
	{

		if ((!e->isBoss())&&(e->getPosition().getDistance(position)<_explodeRadius))
		{
			float damageContributed  = e->onRealDamaged(_explodeDamage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed );
		}


	}
}
