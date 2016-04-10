#include "BuffTypeExplodeOnDeath.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DamageContributionManager.h"
#include "SoundManager.h"
#include "ParticleEmitterManager.h"
#include "BuffTypeSlow.h"


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





void BuffTypeExplodeOnDeath::setAppearacneWithTarget( Enemy* target , bool show )
{

	if (show)
	{
		target->setBuffExplodeOnDeathState(true);

		SoundManager::getInstance()->playSoundEffect("sound/buff_eod.mp3");

		ParticleSystem* eod_buff = ParticleSystemQuad::create("effects/Particle_ExplodeOnDeath_buff.plist");
		eod_buff->setPosition(getContentSize().width/2,getContentSize().height/2);
		//target->addChild(slow_buff,10,_buffType);
		addChild(eod_buff,10,_buffType);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(eod_buff);
	}
	else
	{
		target->setBuffExplodeOnDeathState(false);

		if (getChildByTag(_buffType)!= nullptr)
		{

			((ParticleSystem*)(getChildByTag(_buffType)))->setEmissionRate(0);
			ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(((ParticleSystem*)(getChildByTag(_buffType))));
			ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(((ParticleSystem*)(getChildByTag(_buffType))));

		}
	}
}

void BuffTypeExplodeOnDeath::explodeOnDeath(Point position)
{
	//Point p = ((Sprite*)(event->getUserData()))->getPosition();
	auto enemyManager = EnemyManager::getInstance();
	for (Enemy* e : enemyManager->enemiesInSequence)
	{

		if ((e->getPosition().getDistance(position)<_explodeRadius))
		{
			//float damageContributed  = e->onRealDamaged(888);
			float damageContributed  = e->onMagicalDamaged(_explodeDamage);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed );
			e->setBuff(BuffTypeSlow::create(e,0.55,0.6));
		}


	}


	//特效
	ParticleSystem* superPower = ParticleSystemQuad::create("effects/Particle_ExplodeOnDeath_explode.plist");
	addChild(superPower);
	superPower->setPosition(getPosition());
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(superPower);


}
