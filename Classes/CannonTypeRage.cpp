#include "CannonTypeRage.h"
#include "Bullet.h"
#include "NumericalManager.h"

USING_NS_CC;

const int rage_tag = 12;


bool CannonTypeRage::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Rage.png");


	_attackIntervalWhenRage = 0.19*_attackInterval;

	_rage = false;
	_countForRage = 0;

	return true;
}




void CannonTypeRage::attackOnce()
{

	Bullet* bullet = Bullet::create();
	if (_rage)
	{
		bullet->setPosition(getPositionX()+ (-25 + CCRANDOM_0_1()*50) , getPositionY());
	}
	else
	{
		bullet->setPosition(getPosition());
	}
	
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	if (!_rage)
	{
		_countForRage++;
		if (_countForRage>=4)
		{
			setRage(true);
		}
	}

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_rage.wav");

}



void CannonTypeRage::update( float delta )
{


	if (!readyToShoot)
	{
		if (_rage)
		{
			_iterator++;
			if (_iterator>=_attackIntervalWhenRage)
			{
				readyToShoot = true;
				_iterator=0;
			}
		}
		else
		{
			_iterator++;
			if (_iterator>=_attackInterval)
			{
				readyToShoot = true;
				_iterator=0;
			}
		}


	}

	if (em->enemiesInSequence.size()==0)
	{
		isAttacking = false;
		if (_rage)
		{
			setRage(false);
		}
		else
		{
			_countForRage = 0;
		}
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
			
			if (_rage)
			{
				setRage(false);
			}
			else
			{
				_countForRage = 0;
			}
			
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

void CannonTypeRage::setRage( bool rage )
{
	_rage = rage;
	if (rage)
	{
		setRotation(0);
		setTexture("cannons/CannonCover_Rage_base.png");
		Vec2 v = Vec2(getContentSize().width/2 , getContentSize().height/2);
		for (int i=0 ; i<4 ; i++)
		{

			auto sp = Sprite::create("cannons/CannonCover_Rage_rage.png");
			addChild(sp);
			sp->setTag(rage_tag+i);
			sp->setPosition(v.x + 25*cos(i * CC_DEGREES_TO_RADIANS(90)), v.y + 25*sin(i* CC_DEGREES_TO_RADIANS(90)));
			
		}
		RotateBy* ro = RotateBy::create(1,360);
		RepeatForever* rept = RepeatForever::create(ro);
		runAction(rept);

	}
	else
	{
		stopAllActions();
		_countForRage = 0;
		setTexture("cannons/CannonCover_Rage.png");
		float direction = getChildByTag(rage_tag)->getRotation()+ getRotation();
		setRotation(direction);
		for (int i = 0;i<4; i++)
		{
			if (getChildByTag(rage_tag+i)!=nullptr)
			{
				removeChildByTag(rage_tag+i);

			}
		}

		
	}
}

void CannonTypeRage::setDirection()
{
	if (_rage)
	{
		
		Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
		for (int i = 0;i<4; i++)
		{
			if (getChildByTag(rage_tag+i)!=nullptr)
			{
				getChildByTag(rage_tag+i)->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90 - getRotation());

			}
		}
	}
	else
	{
		Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
		setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
	}
}

void CannonTypeRage::tryGetTarget()
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
