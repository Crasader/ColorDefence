#include "BuffTypeExplodeOnDeath.h"
#include "Enemy.h"


USING_NS_CC;

bool BuffTypeExplodeOnDeath::init(Enemy* enemy, float buffTime)
{

	if ( !Buff::init() )
	{
		return false;
	}

	_buffType = BuffType::kBuffTypeExplodeOnDeath;
	//_buffType = 6;


	_buffTimeRest = buffTime;

	return true;
}

void BuffTypeExplodeOnDeath::makeEffectWithTarget(Enemy* target)
{

	Buff::makeEffectWithTarget(target);
	
}

BuffTypeExplodeOnDeath* BuffTypeExplodeOnDeath::create(Enemy* enemy, float buffTime)
{

	BuffTypeExplodeOnDeath *pRet = new BuffTypeExplodeOnDeath(); 
	if (pRet && pRet->init( enemy, buffTime)) 
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

	return;

	if (show)
	{
		target->setSpreadDamageState(true);
		//显示一个大圆
   		Sprite* sp = Sprite::create("effects/BuffTypeSpreadDamage.png");
		target->addChild(sp,10,_buffType);
 		sp->setPosition(getContentSize().width/2,getContentSize().height/2);
 		sp->setScale(500.0/600.0);
		auto fi = FadeIn::create(2.0);
		auto fo = FadeOut::create(2.0);
  		Sequence* seq = Sequence::create(fi,fo,nullptr);
		sp->runAction(RepeatForever::create(seq));
 		sp->runAction(RepeatForever::create(RotateBy::create(20,1080)));

	}
	else
	{
		target->setSpreadDamageState(false);
		//隐藏大圆
 		if (target->getChildByTag(_buffType)!= nullptr)
		{

			target->removeChildByTag(_buffType);

		}
	}
}
