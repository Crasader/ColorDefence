#include "CannonTypeSpreadOnBoss.h"
#include "BulletTypeSpreadOnBoss.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeSpreadOnBoss::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_SpreadOnBoss_base.png");

	_core = Sprite::create("cannons/CannonCover_SpreadOnBoss_core.png");
	addChild(_core);
	_core->setPosition(getContentSize()/2);

	return true;
}




void CannonTypeSpreadOnBoss::attackOnce()
{



	BulletTypeSpreadOnBoss* bullet = BulletTypeSpreadOnBoss::create();
	
	getParent()->addChild(bullet);
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 12.0 + 18.0* (float)_color.r / 255);

	bullet->setTarget(_target);
	bullet->setDamageContributerID(_damageContributerID);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_sob.mp3");



}

void CannonTypeSpreadOnBoss::tryGetTarget()
{


	Vector<Enemy*> v_target = Vector<Enemy*>();
	for (Enemy* e: em->enemiesInSequence)
	{
		if ((e->isBoss())&&(getPosition().getDistance(e->getPosition())<=attackRange))
		{
			v_target.pushBack(e);
		}
	}


	if (v_target.empty())
	{
		Cannon::tryGetTarget();
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

void CannonTypeSpreadOnBoss::setDirection()
{
	Cannon::setDirection();
	if (_target->isBoss())
	{
		_core->setRotation(_core->getRotation()+5);
	}
	
}

void CannonTypeSpreadOnBoss::update( float delta )
{
	if (!readyToShoot)
	{
		_iterator += 60.0 * delta;
		if (_iterator>=_attackInterval)
		{
			readyToShoot = true;
			_iterator-= _attackInterval;
		}

	}


	if (em->enemiesInSequence.size()==0)
	{
		isAttacking = false;
		_core->setRotation(0);
		return;
	}

	//若正在攻击
	if (isAttacking)
	{


		//若攻击对象死了或超出范围
		if ((!_target->isAlive())||(this->getPosition().getDistance(_target->getPosition())>attackRange)||(_target->isFloating))
		{
			isAttacking = false;
			_target = nullptr;
			_core->setRotation(0);
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
