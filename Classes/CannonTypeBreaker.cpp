#include "CannonTypeBreaker.h"
#include "BulletTypeBreaker.h"
#include "NumericalManager.h"


const int color_tag = 111;
USING_NS_CC;

bool CannonTypeBreaker::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Breaker_base.png");

	_readyBullet = Sprite::create("effects/Bullet_Breaker.png");
	addChild(_readyBullet,10086);
	_readyBullet->setPosition(getContentSize().width/2 , getContentSize().height/2 + 21);

	_handle = Sprite::create("BLANK.png");
	addChild(_handle,10085);
	_handle->setPosition(getContentSize()/2);
	_handle->setScaleX(4);

	return true;
}




void CannonTypeBreaker::attackOnce()
{


	Point p = _target->getPosition();
	float dis = getPosition().getDistance(p) - 20;

	_readyBullet->stopAllActions();
	_handle->stopAllActions();
	_readyBullet->setPosition(getContentSize().width/2 , getContentSize().height/2 + 21);
	_handle->setPosition(getContentSize()/2);
	_handle->setScale(4,1);
	
	
	

	


	//bullet->setTarget(_target);

	auto st = CallFunc::create([&](){

		if (_target != nullptr)
		{
			BulletTypeBreaker* bullet = BulletTypeBreaker::create();
			bullet->setPosition(getPosition());
			bullet->setRotation(getRotation());
			bullet->setDamage(_damage, 30 , 350);
			bullet->setDamageContributerID(_damageContributerID);
			getParent()->addChild(bullet);
			bullet->setTarget(_target);
			

		}


	});


	auto mb = MoveBy::create(0.1,Vec2(0,dis));

	_readyBullet->runAction(Sequence::create(mb,st,mb->reverse(),nullptr));



	auto mb_h = MoveBy::create(0.1f,Vec2(0,dis/2));
	auto sb_h = ScaleBy::create(0.1f,1,dis);
	auto sp1 = Spawn::create(mb_h,sb_h,nullptr);
	auto sp2 = Spawn::create(mb_h->reverse(),sb_h->reverse(),nullptr);

	_handle->runAction(Sequence::create(sp1,sp2,nullptr));

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_breaker.wav");


	isAttacking = false;
	_target = nullptr;

}

void CannonTypeBreaker::pause()
{
	Cannon::pause();
	_readyBullet->pause();
	_handle->pause();
}

void CannonTypeBreaker::resume()
{
	Cannon::resume();
	_readyBullet->resume();
	_handle->resume();
}


void CannonTypeBreaker::setDirection()
{

	if (_handle->getScaleY() > 1.2 )
	{
		return;
	}
	Cannon::setDirection();
}

