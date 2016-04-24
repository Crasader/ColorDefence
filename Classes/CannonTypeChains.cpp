#include "CannonTypeChains.h"
#include "NumericalManager.h"
#include "EnemyManager.h"
#include "BulletTypeChains.h"

USING_NS_CC;

bool CannonTypeChains::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Chains_base.png");

	for (int i = 0 ; i<6 ; i++)
	{
		_catchers[i] = Sprite::create("cannons/CannonCover_Chains_catcher.png");
		addChild(_catchers[i],i+1);
		_catchers[i]->setPosition(getContentSize()/2);
		_catchers[i]->setRotation((float)i * 60);

	}

	_stunTime = 0.83;

	return true;
}




void CannonTypeChains::attackOnce()
{


	int amountOfTargets = 0;


	EnemyManager* em = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if ((getPosition().getDistance(e->getPosition())<= attackRange)&&(!e->isAntiMagic()))
		{

			BulletTypeChains* chain = BulletTypeChains::create();
			chain->setPosition(getPosition());
			getParent()->addChild(chain,-1);
			chain->setDamage(_damage, _stunTime);
			chain->setDamageContributerID(_damageContributerID);
			chain->setTarget(e);
			amountOfTargets++ ;
			//chain->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));


		}
	}

	if (amountOfTargets>6)
	{
		amountOfTargets = 6;
	}


	for (int i = 0 ; i< amountOfTargets ; i++)
	{
		_catchers[i]->stopAllActions();
		_catchers[i]->setRotation((float)i * 60 - 18 + CCRANDOM_0_1()*36);
		_catchers[i]->setOpacity(255);
		auto fo = FadeOut::create(0.01);
		auto dt = DelayTime::create(_stunTime + 0.1);
		auto fi = FadeIn::create(0.01);
		
		_catchers[i]->runAction(Sequence::create(fo,dt,fi,nullptr));

	}

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_chain.wav");


}

void CannonTypeChains::setDirection()
{
	setRotation(getRotation()-2);
	return;
}

void CannonTypeChains::tryGetTarget()
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

void CannonTypeChains::pause()
{
	Cannon::pause();
	for (int i = 0 ; i <6 ; i++)
	{
		_catchers[i]->pause();
	}
}

void CannonTypeChains::resume()
{
	Cannon::resume();
	for (int i = 0 ; i <6 ; i++)
	{
		_catchers[i]->resume();
	}
}

