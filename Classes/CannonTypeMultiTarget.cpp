#include "CannonTypeMultiTarget.h"
#include "BulletTypeMultiTarget.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeMultiTarget::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_MultiTarget.png");

	hasExtraState = true;
	extraStateOn = false;

	return true;
}




void CannonTypeMultiTarget::attackOnce()
{

	if (extraStateOn)
	{
		EnemyManager* em = EnemyManager::getInstance();
		Vector<Enemy*> _targets = Vector<Enemy*>();
		for (Enemy* e : em->enemiesInSequence)
		{
			if ((getPosition().getDistance(e->getPosition())<= attackRange)&&(!e->isAntiMagic()))
			{

				_targets.pushBack(e);

			}
		}
		float dtt = _attackInterval/(_targets.size()+1);
		Vector<FiniteTimeAction*> actions = Vector<FiniteTimeAction*>();
		for (auto e:_targets)
		{


				BulletTypeMultiTarget* bullet = BulletTypeMultiTarget::create();
				bullet->setPosition(getPosition());
				bullet->setRotation(getRotation());
				bullet->setDamage(_damage/6);
				bullet->setDamageContributerID(_damageContributerID);

				getParent()->addChild(bullet);


				//
				int c3b[3];
				c3b[0] = getColorInfo().r;
				c3b[1] = getColorInfo().g;
				c3b[2] = getColorInfo().b;
				for (int i=0 ; i<3 ; i++)
				{
					c3b[i] = c3b[i] -50 + CCRANDOM_0_1()*100;
					if (c3b[i]>255)
					{
						c3b[i] = 255;
					}
					else if(c3b[i]<0)
					{
						c3b[i] = 0;
					}
				}
				bullet->setColor(NumericalManager::getInstance()->getBulletColor(Color3B(c3b[0],c3b[1],c3b[2])));
				//

				bullet->setTarget(e);


		}

		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_multiTarget_on.mp3");

	}
	else
	{

		BulletTypeMultiTarget* bullet = BulletTypeMultiTarget::create();
		bullet->setPosition(getPosition());
		bullet->setRotation(getRotation());
		bullet->setDamage(_damage);
		bullet->setDamageContributerID(_damageContributerID);

		getParent()->addChild(bullet);
		
		

		//
		bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
		//

		bullet->setTarget(_target);

		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_multiTarget.mp3");



	}








}

void CannonTypeMultiTarget::setDirection()
{

	if (extraStateOn)
	{
		setRotation(getRotation()-3);
	}
	else
	{

		Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
		setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
	}


}

void CannonTypeMultiTarget::setExtraState( bool on )
{

	Cannon::setExtraState(on);
	if (on)
	{
		setTexture("cannons/CannonCover_MultiTarget_on.png");
	}
	else
	{
		setTexture("cannons/CannonCover_MultiTarget.png");
	}
	
}

void CannonTypeMultiTarget::tryGetTarget()
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

