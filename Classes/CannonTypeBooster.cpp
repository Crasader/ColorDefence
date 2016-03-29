#include "CannonTypeBooster.h"
#include "NumericalManager.h"
#include "BulletTypeBoost.h"
#include "CannonManager.h"

USING_NS_CC;

bool CannonTypeBooster::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Booster_base.png");

	canBeBoosted = false;

	return true;
}




void CannonTypeBooster::attackOnce()
{



	BulletTypeBoost* bullet = BulletTypeBoost::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_targetCannon);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//





}

void CannonTypeBooster::tryGetTarget()
{
	CannonManager* cm = CannonManager::getInstance();
	Vector<Cannon*> v_targetCannon = Vector<Cannon*>();
	for (Cannon* c: cm->cannons)
	{
		if ((c->canBeBoosted)&&(!c->isBoosted)&&(getPosition().getDistance(c->getPosition())<=attackRange))
		{
			v_targetCannon.pushBack(c);
		}
	}


	if (v_targetCannon.empty())
	{
		return;
	}

	_targetCannon = v_targetCannon.front();

	for (Cannon* c : v_targetCannon)
	{
		if (getPosition().getDistance(c->getPosition())<=getPosition().getDistance(_targetCannon->getPosition()))
		{
			_targetCannon = c;
			isAttacking = true;
		}
	}
}

void CannonTypeBooster::update( float delta )
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


		//若攻击对象死了或超出范围
		if ((_targetCannon->isBoosted))
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
	//若不在攻击
	else
	{


		//如果有进入范围的
		tryGetTarget();

	}

}

void CannonTypeBooster::setDirection()
{
	Point normalized = ccpNormalize(ccp(_targetCannon->getPosition().x - getPosition().x,	_targetCannon->getPosition().y - getPosition().y));
	setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
}

