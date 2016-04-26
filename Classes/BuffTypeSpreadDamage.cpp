#include "BuffTypeSpreadDamage.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DamageContributionManager.h"
#include "ParticleEmitterManager.h"
#include "SoundManager.h"


USING_NS_CC;

bool BuffTypeSpreadDamage::init(Enemy* enemy, float buffTime, float damageSpread)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeSpreadDamage;
	//_buffType = 5;


	_buffTimeRest = buffTime;

	_damageSpread = damageSpread;





	return true;
}


BuffTypeSpreadDamage* BuffTypeSpreadDamage::create(Enemy* enemy, float buffTime, float damageSpread)
{

	BuffTypeSpreadDamage *pRet = new BuffTypeSpreadDamage(); 
	if (pRet && pRet->init( enemy, buffTime , damageSpread)) 
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

void BuffTypeSpreadDamage::overrideWithNewBuff( Buff* newBuff )
{

	_buffTimeRest = _buffTimeRest>((BuffTypeSpreadDamage*)newBuff)->_buffTimeRest?_buffTimeRest:((BuffTypeSpreadDamage*)newBuff)->_buffTimeRest;
	_damageSpread = _damageSpread>((BuffTypeSpreadDamage*)newBuff)->_damageSpread?_damageSpread:((BuffTypeSpreadDamage*)newBuff)->_damageSpread;
}



bool BuffTypeSpreadDamage::verifyWithTarget( Enemy* target )
{
	if ((!target->isAlive())||(target->isFloating))
	{
		return false;
	}

	if (!target->isBoss())
	{
		return false;
	}

	return true;
}

void BuffTypeSpreadDamage::setAppearacneWithTarget( Enemy* target , bool show )
{
	if (show)
	{
		target->setSpreadDamageState(true);
		//显示一个大圆
   		Sprite* sp = Sprite::create("effects/BuffTypeSpreadDamage.png");
		addChild(sp,10,_buffType);
 		sp->setPosition(getContentSize().width/2,getContentSize().height/2);
 		sp->setScale(0.6);
		sp->runAction(ScaleTo::create(0.2,1));
		auto fi = FadeIn::create(2.0);
		auto fo = FadeOut::create(2.0);
  		Sequence* seq = Sequence::create(fi,fo,nullptr);
		sp->runAction(RepeatForever::create(seq));
 		sp->runAction(RepeatForever::create(RotateBy::create(20,1080)));


		SoundManager::getInstance()->playSoundEffect("sound/buff_sob.mp3");

	}
	else
	{
		target->setSpreadDamageState(false);
		//隐藏大圆
 		if (getChildByTag(_buffType)!= nullptr)
		{

			removeChildByTag(_buffType);

		}
	}
}

void BuffTypeSpreadDamage::spreadDamage(Point position)
{
	//Point p = ((Sprite*)(event->getUserData()))->getPosition();
	auto enemyManager = EnemyManager::getInstance();
	for (Enemy* e : enemyManager->enemiesInSequence)
	{

		if ((!e->isBoss())&&(e->getPosition().getDistance(position)<250))
		{
			float damageContributed  = e->onRealDamaged(_damageSpread);
			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed );
		}


	}

	//特效
	ParticleSystem* superPower = ParticleSystemQuad::create("effects/Particle_SpreadOnBoss.plist");
	addChild(superPower);
	superPower->setPosition(getPosition());
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(superPower);





}
