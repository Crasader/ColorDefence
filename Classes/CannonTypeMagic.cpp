#include "CannonTypeMagic.h"
#include "BulletTypeMagic.h"
#include "NumericalManager.h"

USING_NS_CC;

const int color_tag = 111;


bool CannonTypeMagic::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Magic_base.png");

	_core = Sprite::create("cannons/CannonCover_Magic_core.png");
	

	getChildByTag(color_tag)->addChild(_core);
	((Sprite*)getChildByTag(color_tag))->setTexture("cannons/CannonCover_Magic_color.png");
	((Sprite*)getChildByTag(color_tag))->setZOrder(2);
	
	_core->setPosition(((Sprite*)getChildByTag(color_tag))->getContentSize()/2);
	fading = true;

	return true;
}




void CannonTypeMagic::attackOnce()
{

	BulletTypeMagic* bullet = BulletTypeMagic::create();
	bullet->setPosition(getPosition());
	bullet->setDamageContributerID(_damageContributerID);
	bullet->setDamage(_damage);

	getParent()->addChild(bullet);
	bullet->setTarget(_target);

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_magic.wav");

}



void CannonTypeMagic::tryGetTarget()
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

void CannonTypeMagic::setDirection()
{

	Cannon::setDirection();
	getChildByTag(color_tag)->setRotation(getRotation()*(-1));

	
	if (fading)
	{
		_core->setOpacity(_core->getOpacity()-10);
		if (_core->getOpacity()<=10)
		{
			fading = false;
		}
	}
	else
	{
		_core->setOpacity(_core->getOpacity()+10);
		if (_core->getOpacity()>=245)
		{
			fading = true;
		}
	}


}



void CannonTypeMagic::update( float delta )
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
		_core->setOpacity(255);
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
			fading = true;
			_core->setOpacity(255);
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

