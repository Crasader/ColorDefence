#include "CannonTypeBridge.h"
#include "NumericalManager.h"
#include "BulletTypeBridge.h"
#include "CannonManager.h"
#include "EnemyManager.h"

USING_NS_CC;

bool CannonTypeBridge::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Bridge.png");

	_attackingCannon = false;



	return true;
}

void CannonTypeBridge::attackOnce()
{

	

	BulletTypeBridge* bullet = BulletTypeBridge::create();


	if (_attackingCannon)
	{

		bullet->setTarget(_targetCannon);


	}
	else
	{
		bullet->setTarget(_target);
	}
	

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage,_attackingCannon, 135);
	bullet->setDamageContributerID(_damageContributerID);

	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//


	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_bridge.mp3");


}

void CannonTypeBridge::tryGetTarget()
{
	
	_attackingCannon = false;
	if (!(EnemyManager::getInstance()->enemiesInSequence.empty()))
	{
		Cannon::tryGetTarget();

	}
	
	if (_target == nullptr)
	{
		_attackingCannon = tryGetTargetCannon();
	}


}

void CannonTypeBridge::update( float delta )
{
	if (!readyToShoot)
	{
		_iterator++;
		if (_iterator>=_attackInterval)
		{
			readyToShoot = true;
			_iterator=0;
		}

	}



	//若正在攻击
	if (isAttacking)
	{
		if (_attackingCannon)
		{

			

			if (readyToShoot)
			{
				
				if (tryGetTargetCannon())
				{
					setDirection();
					readyToShoot = false;
					attackOnce();
					//tryGetTarget();
				}
				else
				{
					//isAttacking = false;
					_attackingCannon = false;
					//return;
				}
				isAttacking = false;
				_targetCannon = nullptr;

			}


		}
		else
		{

			//若攻击对象死了或超出范围
			if ((!_target->isAlive())||(this->getPosition().getDistance(_target->getPosition())>attackRange)||(_target->isFloating))
			{
				isAttacking = false;
				_target = nullptr;
				return;
			}

			setDirection();

			if (readyToShoot)
			{
				readyToShoot = false;
				attackOnce();

			}


		}




	}
	//若不在攻击
	else
	{


		//如果有进入范围的
		tryGetTarget();

	}

}

void CannonTypeBridge::setDirection()
{
	if (_attackingCannon)
	{

		Point normalized = ccpNormalize(ccp(_targetCannon->getPosition().x - getPosition().x, _targetCannon->getPosition().y - getPosition().y));
		setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
	}
	else
	{
		Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
		setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
	}

}

bool CannonTypeBridge::getAttackingState()
{

	//return Cannon::getAttackingState();
	return (isAttacking&&(!_attackingCannon));

}

bool CannonTypeBridge::tryGetTargetCannon()
{
	CannonManager* cm = CannonManager::getInstance();
	Vector<Cannon*> v_targetCannon = Vector<Cannon*>();
	if (cm->cannons.empty())
	{
		return false;
	}
	for (Cannon* c: cm->cannons)
	{
		if ((c->getAttackingState())&&(getPosition().getDistance(c->getPosition())<=attackRange)&&(c!=this)&&(c->isActioning()))
		{
			v_targetCannon.pushBack(c);
		}
	}


	if (!v_targetCannon.empty())
	{
		_targetCannon = v_targetCannon.front();
		isAttacking = true;

		for (Cannon* c : v_targetCannon)
		{
			if (getPosition().getDistance(c->getPosition())<=getPosition().getDistance(_targetCannon->getPosition()))
			{
				_targetCannon = c;

			}
		}

		_attackingCannon = true;
		return true;
	}
	return false;
}

