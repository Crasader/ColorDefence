#include "CannonTypePoisonousMulti.h"
#include "BulletTypePoisonousMulti.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypePoisonousMulti::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_PoisonousMulti_base.png");

	_canRotate = true;

	_core = Sprite::create("cannons/CannonCover_PoisonousMulti_core.png");
	addChild(_core);
	_core->setPosition(getContentSize()/2);


	return true;
}




void CannonTypePoisonousMulti::attackOnce()
{

	_canRotate = false;

	BulletTypePoisonousMulti* bullet = BulletTypePoisonousMulti::create();
	getParent()->addChild(bullet);

	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange,53.0 ,26.5);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_splash.wav");

	DelayTime* dt = DelayTime::create(0.8);
	CallFunc* cf = CallFunc::create([&](){

		_canRotate = true;

	});
	Sequence* seq = Sequence::create(dt,cf,NULL);
	runAction(seq);

	
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_poisonousMulti.mp3");


	isAttacking = false;
	_target = nullptr;


}

void CannonTypePoisonousMulti::setDirection()
{
	if (_canRotate)
	{
		Cannon::setDirection();
	}


		
	if (_core->getScale()<=2.0)
	{
		_core->setScale(_core->getScale()+0.1);
	}


}

void CannonTypePoisonousMulti::update( float delta )
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
		_core->setScale(1);
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
			_core->setScale(1);
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

