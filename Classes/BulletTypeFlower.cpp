#include "BulletTypeFlower.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "NumericalManager.h"

USING_NS_CC;

bool BulletTypeFlower::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	//setTexture("effects/Bullet_Splash.png");

	Vec2 v = getContentSize()/2;
	for (int i = 0; i < 5; i++)
	{
		_petal[i] = Sprite::create("effects/Bullet_Flower.png");
		addChild(_petal[i]);
		_petal[i]->setAnchorPoint(Point(0.5,0));
		_petal[i]->setPosition(v.x + 20*cos(i * CC_DEGREES_TO_RADIANS(72)-CC_DEGREES_TO_RADIANS(90)), v.y + 20*sin(i* CC_DEGREES_TO_RADIANS(72)-CC_DEGREES_TO_RADIANS(90)));
		_petal[i]->setRotation(180 - i*72);
		_petal[i]->setCascadeOpacityEnabled(true);

		auto _petal_cover = Sprite::create("effects/Bullet_Flower_cover.png");
		_petal[i]->addChild(_petal_cover);
		_petal_cover->setPosition(_petal[i]->getContentSize()/2);
		
		//_petal[i]->setOpacity(100);
		//_petal_cover->setOpacity(100);

	}

	_damageRadius = 0;
	setOpacity(0);
	setRotation(CCRANDOM_0_1()*72.0);
	runAction(RepeatForever::create(RotateBy::create(10,-200)));

	return true;
}



void BulletTypeFlower::explode()
{


	bloom();



	//¶¯»­
	//setTexture("effects/Bullet_Shadow.png");


	auto ex1 = DelayTime::create(0.2f);
	auto ex2 = CallFunc::create([&]{

		performDamage();

	});


	auto ex3 = DelayTime::create(1.4);
	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex1,ex2,ex3,ex4,NULL));



}

void BulletTypeFlower::setDamage( float damage , float damageRaius )
{
	_damage = damage;
	_damageRadius = damageRaius;
}

void BulletTypeFlower::setTarget( Enemy* enemy )
{
	_target = enemy;

	explode();



}

void BulletTypeFlower::setPetalColor( Color3B c3b )
{
	for (int i =0;i<5;i++)
	{
		_petal[i]->setColor(NumericalManager::getInstance()->getBulletColor(c3b));
	}

}

void BulletTypeFlower::bloom()
{

	float ratio = 1.2*_damageRadius / ( _petal[0]->getContentSize().height + 10);

	for (int i =0 ;i<5;i++)
	{
		_petal[i]->setScale(0.1,0);
		auto act1 = ScaleTo::create(2,ratio);
		auto act2 = FadeOut::create(1.2);
		auto act3 = Spawn::create(act1,act2,NULL);
		_petal[i]->runAction(act3);
	}
}

void BulletTypeFlower::performDamage()
{
		//Point pt = _target->getPosition();
	Point pt = getPosition();
	EnemyManager* em  = EnemyManager::getInstance();
	for (Enemy* e : em->enemiesInSequence)
	{
		if ((pt.getDistance(e->getPosition())<_damageRadius)&&(!e->isAntiMagic()))
		{
			e-> onMagicalDamaged(_damage);

		}

	}
}

void BulletTypeFlower::pause()
{
	Bullet::pause();
	for (int i=0;i<5;i++)
	{
		_petal[i]->pause();
	}
}

void BulletTypeFlower::resume()
{
	Bullet::resume();
	for (int i=0;i<5;i++)
	{
		_petal[i]->resume();
	}
}


