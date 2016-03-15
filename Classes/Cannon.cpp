#include "Cannon.h"
#include "Bullet.h"
#include "NumericalManager.h"
#include "GameStateManager.h"
#include "MapPointsManager.h"



USING_NS_CC;
const int color_tag = 111;
const int color_z_order = -5;

bool Cannon::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}

	_cannonType = 0;
	//_price = 0;

	setTexture("cannons/CannonCover.png");
	auto color = Sprite::create("cannons/CannonColor.png");
	addChild(color,color_z_order,color_tag);
	color->setPosition(Point(getContentSize().width/2,getContentSize().height/2));




	hasExtraState = false;
	extraStateOn = false;

	canBeBoosted = true;
	boostFactor = 1.0;
	isBoosted = false;
	

	attackRange = 330;
	_damage = 100;
	_attackInterval = 20;

	_iterator = 0;
	readyToShoot = false;
	isAttacking = false;
	_target = nullptr;

	em = EnemyManager::getInstance();

	if (GameStateManager::getInstance()->currentActioningState)
	{
		_isActioning = true;
		schedule(schedule_selector(Cannon::update), 1.0f/60.0f);

	}
	else
	{
		_isActioning = false;
	}

	hasBaseAfterDestroyed = true;

	_damageContributerID = 0;

	return true;
}



void Cannon::tryGetTarget()
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

	}

}




void Cannon::update( float delta )
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

	//若正在攻击
	if (isAttacking)
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
	//若不在攻击
	else
	{



		//如果有进入范围的
		tryGetTarget();

	}


}


void Cannon::setDirection()
{

	Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
	setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
}

void Cannon::attackOnce()
{

	Bullet* bullet = Bullet::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	
	if (isBoosted)
	{
		bullet->setDamage(10*_damage);
		isBoosted = false;
	}
	else
	{
		bullet->setDamage(_damage);
	}


	bullet->setTarget(_target);
	bullet->setDamageContributerID(_damageContributerID);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_normal.mp3");


}

void Cannon::setColorInfo( cocos2d::Color3B c3b )
{
	(this->getChildByTag(color_tag))->setColor(c3b);

	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);
	if (extraStateOn)
	{
		std::vector<float> extraStatefactor = nm->getExtraStateFactor(_cannonType);
		_damage = _damage * extraStatefactor[0];
		attackRange = attackRange* extraStatefactor[1];
		_attackInterval * extraStatefactor[2];
		
	}

}

unsigned Cannon::getCannonType()
{
	return _cannonType;
}

cocos2d::Color3B Cannon::getColorInfo()
{
	return ((Sprite*)(this->getChildByTag(color_tag)))->getColor();
}

void Cannon::setCannonType( unsigned type )
{

	_cannonType = type;
}

void Cannon::pause()
{
	_isActioning = false;
	Sprite::pause();
}

void Cannon::resume()
{
	_isActioning = true;
	Sprite::resume();
}

void Cannon::setExtraState( bool on )
{
	extraStateOn = on;
}

bool Cannon::getAttackingState()
{
	return isAttacking;

}

bool Cannon::isActioning()
{
	return _isActioning;
}

void Cannon::onExit()
{
	Sprite::onExit();
}

void Cannon::setDamageContributerID()
{
	_damageContributerID = MapPointsManager::getIndexByPoint(getPosition());
}




