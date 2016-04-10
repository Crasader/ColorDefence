#include "CannonTypeTriple.h"
#include "NumericalManager.h"
#include "Bullet.h"

USING_NS_CC;

const int color_tag = 111;
const int color_z_order = -1;

bool CannonTypeTriple::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Triple_base.png");
	Vec2 v = Vec2(getContentSize().width/2 , getContentSize().height/2);
	((Sprite*)getChildByTag(color_tag))->setTexture("cannons/CannonCover_Triple_color.png");
	for (int i= 0;i<3;i++)
	{
		Sprite* sp = Sprite::create("cannons/CannonCover_Triple_single.png");
		addChild(sp);
		sp->setPosition(v.x + 24.8*cos(i * CC_DEGREES_TO_RADIANS(120)+CC_DEGREES_TO_RADIANS(90)), v.y + 24.8*sin(i* CC_DEGREES_TO_RADIANS(120)+CC_DEGREES_TO_RADIANS(90)));
		_childCannons[i] = sp;

	}

	for (int i=0 ; i<3 ;i++)
	{
		_iterator_3[i] = 0;
		readyToShoot_3[i] = false;
		isAttacking_3[i] = false;
		_targets[i] = nullptr;
	}


	return true;
}




void CannonTypeTriple::attackOnce(int index)
{
	
	Bullet* bullet = Bullet::create();


	bullet->setPosition(convertToWorldSpace(_childCannons[index]->getPosition()));
	bullet->setRotation(_childCannons[index]->getRotation());
	bullet->setDamage(_damage);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_targets[index]);
	getParent()->addChild(bullet);


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_triple.wav");

}



void CannonTypeTriple::update( float delta )
{

	if (em->enemiesInSequence.size()==0)
	{
		isAttacking = false;
		for (int i =0;i<3;i++)
		{
			isAttacking_3[i]=false;
		}
		return;
	}

	//setDirection();

	for (int i=0;i<3;i++)
	{
		if (!readyToShoot_3[i])
		{
			_iterator_3[i] += 60.0 * delta;
			if (_iterator_3[i]>=_attackInterval)
			{
				readyToShoot_3[i] = true;
				_iterator_3[i] -= _attackInterval;
			}

		}




		//若正在攻击
		if (isAttacking_3[i])
		{


			//若攻击对象死了或超出范围
			if ((!_targets[i]->isAlive())||(this->getPosition().getDistance(_targets[i]->getPosition())>attackRange)||(_targets[i]->isFloating))
			{
				isAttacking_3[i] = false;
				_targets[i] = nullptr;
				return;
			}

			
			setDirection(i);

			if (readyToShoot_3[i])
			{
				readyToShoot_3[i] = false;
				attackOnce(i);

			}






		}
		//若不在攻击
		else
		{


			//如果有进入范围的
			tryGetTarget(i);

		}
	}

	

}

void CannonTypeTriple::tryGetTarget(int index)
{
	Vector<Enemy*> targetsTemp(em->enemiesInSequence);
	for (int j = 0;j<3;j++)
	{
		if (_targets[j]!=nullptr)
		{
			targetsTemp.eraseObject(_targets[j]);
		}
	}
	if (targetsTemp.empty())
	{
		return;
	}

	_targets[index] = targetsTemp.front();

	for (Enemy*e : targetsTemp)
	{



		if (getPosition().getDistance(e->getPosition())<=getPosition().getDistance(_targets[index]->getPosition()))
		{
			_targets[index] = e;
		}


			

	}


	if (getPosition().getDistance(_targets[index]->getPosition())>attackRange)
	{
		_targets[index] = nullptr;
	}
	else
	{
		isAttacking_3[index] = true;

	}

}

void CannonTypeTriple::setDirection(int index)
{

	setDirection();

	Point normalized = ccpNormalize(ccp(_targets[index]->getPosition().x - getPosition().x,	_targets[index]->getPosition().y - getPosition().y));
	_childCannons[index]->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90-getRotation());



}

void CannonTypeTriple::setDirection()
{

		setRotation(getRotation() - 1);

}

bool CannonTypeTriple::getAttackingState()
{
	for (int i = 0 ; i<3 ; i++)
	{
		if (isAttacking_3[i])
		{
			return true;
		}
	}
	return false;
}

