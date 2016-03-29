#include "CannonTypeMagicSlowLine.h"
#include "BulletTypeMagicSlowLine.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeMagicSlowLine::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_MagicSlowLine.png");


	return true;
}




void CannonTypeMagicSlowLine::attackOnce()
{

	stopAllActions();
	ScaleTo* st = ScaleTo::create(0.05,1,0.5);
	//MoveBy* mb = MoveBy::create(0.05,Vect(0,getContentSize().height*0.25));
	ScaleTo* st2 = ScaleTo::create(0.05,1);
	//MoveBy* mb2 = mb->reverse();
	//Spawn* sp = Spawn::create(st,mb,nullptr);
	//Spawn* sp2 = Spawn::create(st2,mb2,nullptr);
	Sequence* seq = Sequence::create(st,st2,nullptr);
	runAction(seq);

	BulletTypeMagicSlowLine* bullet = BulletTypeMagicSlowLine::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 45, 0.6, 24);
	bullet->setDamageContributerID(_damageContributerID);


	bullet->setTarget(_target);
	getParent()->addChild(bullet);


	//
	//bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_magicSlowLine.wav");

}

void CannonTypeMagicSlowLine::tryGetTarget()
{


	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: em->enemiesInSequence)
	{
		if ((!e->isAntiMagic())&&(getPosition().getDistance(e->getPosition())<=attackRange))
		{
			v_target.pushBack(e);
		}
	}


	if (v_target.empty())
	{
		return;
	}

	_target = v_target.front();

	for (Enemy*e : v_target)
	{
		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_target->getPosition()))
		{
			_target = e;
			isAttacking = true;
		}
	}

}

