#include "BulletTypeBoost.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeBoost::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	return true;
}



void BulletTypeBoost::explode()
{


	_targetCannon->isBoosted = true;


	//¶¯»­
	setTexture("effects/splash.png");



	auto ex1 = FadeOut::create(0.5);
	//auto ex2 = RotateBy::create(0.5,-72);
	//auto ex3 = Spawn::create(ex1,ex2,nullptr);

	auto ex4 = CallFunc::create([&]{
		BulletManager::getInstance()->bullets.eraseObject(this);
		removeFromParent();
	});

	runAction(Sequence::create(ex1,ex4,NULL));



}

void BulletTypeBoost::setDamage( float damage)
{
	_damage = damage;

}

void BulletTypeBoost::setTarget( Cannon* cannon )
{
	_targetCannon = cannon;

	MoveTo* move = MoveTo::create(0.1f, _targetCannon->getPosition());
	ActionInstant* explode = CallFunc::create(CC_CALLBACK_0(BulletTypeBoost::explode,this));

	Sequence* sqe = Sequence::create(move,explode,NULL);

	runAction(sqe);
}


