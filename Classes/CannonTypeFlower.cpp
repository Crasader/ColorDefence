#include "CannonTypeFlower.h"
#include "BulletTypeFlower.h"
#include "NumericalManager.h"
#include "CannonManager.h"


USING_NS_CC;
const int color_tag = 111;

bool CannonTypeFlower::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	getChildByTag(color_tag)->setScale(1.15);

	_cannonType = 0;
	setTexture("cannons/CannonCover_Flower_base.png");

	Vec2 v = getContentSize()/2;
	for (int i = 0; i < 5; i++)
	{
		_petal[i] = Sprite::create("cannons/CannonCover_Flower_petal.png");
		addChild(_petal[i]);
		_petal[i]->setAnchorPoint(Point(0.5,0));
		_petal[i]->setPosition(v.x + 30.5*cos(i * CC_DEGREES_TO_RADIANS(72)-CC_DEGREES_TO_RADIANS(90)), v.y + 30.5*sin(i* CC_DEGREES_TO_RADIANS(72)-CC_DEGREES_TO_RADIANS(90)));
		_petal[i]->setRotation(i*(-72));

		auto _petal_cover = Sprite::create("cannons/CannonCover_Flower_petal_cover.png");
		_petal[i]->addChild(_petal_cover);
		_petal_cover->setPosition(_petal[i]->getContentSize()/2);
		//_petal_cover->setAnchorPoint(Point(0.5,0));
	}

	return true;
}




void CannonTypeFlower::attackOnce()
{

	bloom();

	BulletTypeFlower* bullet = BulletTypeFlower::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);


	bullet->setPetalColor(getChildByTag(color_tag)->getColor());



	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_flower.mp3");

	for ( Cannon* c : CannonManager::getInstance()->cannons)
	{
		if ((this != c )&&(c->getCannonType()== 22)&&(c->isActioning()))
		{
			((CannonTypeFlower*)c)->collaborate();
		}
	}

}



void CannonTypeFlower::collaborate()
{


	bloom();

	BulletTypeFlower* bullet = BulletTypeFlower::create();
	bullet->setPosition(getPosition());
	//bullet->setRotation(getRotation()+ CCRANDOM_0_1()*72.0);
	bullet->setDamage(_damage, attackRange);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setPetalColor(getChildByTag(color_tag)->getColor());
	//


	//SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_shadow.mp3");


}

void CannonTypeFlower::setColorInfo( cocos2d::Color3B c3b )
{
	(this->getChildByTag(color_tag))->setColor(c3b);

	for (int i = 0 ; i<5;i++)
	{
		_petal[i]->setColor(c3b);
	}

	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);


}

void CannonTypeFlower::setDirection()
{
	setRotation(getRotation()-1);
}

void CannonTypeFlower::pause()
{
	Cannon::pause();
	for (int i=0;i<5;i++)
	{
		_petal[i]->pause();
	}
}

void CannonTypeFlower::resume()
{
	Cannon::resume();
	for (int i=0;i<5;i++)
	{
		_petal[i]->resume();
	}
}

void CannonTypeFlower::bloom()
{
	for (int i =0 ;i<5;i++)
	{
		_petal[i]->stopAllActions();
		_petal[i]->setScale(1);
		auto act1 = ScaleTo::create(0.2,1.1,-1);
		auto act2 = ScaleTo::create(1.6,1);
		auto act3 = Sequence::create(act1,act2,NULL);
		_petal[i]->runAction(act3);
	}
}

void CannonTypeFlower::tryGetTarget()
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



