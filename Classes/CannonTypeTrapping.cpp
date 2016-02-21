#include "CannonTypeTrapping.h"
#include "BulletTypeTrapping.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeTrapping::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Trapping.png");

	_isTrapping = false;

	return true;
}




void CannonTypeTrapping::attackOnce()
{

	

	BulletTypeTrapping* bullet = BulletTypeTrapping::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_isTrapping?1:_damage, _isTrapping);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	if (!_isTrapping)
	{
		bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	}

	//
	if (_isTrapping)
	{
		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_trapping_trap.mp3");
	}
	else
	{
		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_trapping_normal.mp3");
	}
	

	_isTrapping = false;

}

void CannonTypeTrapping::tryGetTarget()
{
	_target = em->enemiesInSequence.front();

	for (Enemy*e : em->enemiesInSequence)
	{
		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_target->getPosition()))
		{
			_target = e;
		}
	}


	if (getPosition().getDistance(_target->getPosition())>attackRange)
	{
		_target = nullptr;
	}
	else
	{
		isAttacking = true;
		_isTrapping = true;

	}
}

void CannonTypeTrapping::update( float delta )
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


	if (em->enemiesInSequence.size()==0)
	{
		isAttacking = false;
		return;
	}

	//�����ڹ���
	if (isAttacking)
	{


		//�������������˻򳬳���Χ
		if ((!_target->isAlive())||(this->getPosition().getDistance(_target->getPosition())>attackRange*1.2)||(_target->isFloating))
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
	//�����ڹ���
	else
	{


		//����н��뷶Χ��
		tryGetTarget();

	}


}

