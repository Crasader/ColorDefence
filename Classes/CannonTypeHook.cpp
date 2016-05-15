#include "CannonTypeHook.h"
#include "BulletTypeHook.h"
#include "NumericalManager.h"
#include "BuffTypeStun.h"



const int color_tag = 111;
USING_NS_CC;

bool CannonTypeHook::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Hook_base.png");

	_center = Node::create();
	addChild(_center,10086);
	_center->setPosition(getContentSize().width/2 , getContentSize().height/2);

	_readyBullet = Sprite::create("effects/Bullet_Hook.png");
	_center->addChild(_readyBullet,1);
	//_readyBullet->setPosition(getContentSize().width/2 , getContentSize().height/2 + 21);

	_handle = Sprite::create("BLANK.png");
	_center->addChild(_handle,2);
	//_handle->setPosition(getContentSize()/2);
	_handle->setScaleX(4);

	return true;
}




void CannonTypeHook::attackOnce()
{

	if (_target->isMoving())
	{
		_eventDispatcher->dispatchCustomEvent("CANNON_HOOK",this);
	}
	else
	{
		catchOnce( false , Point(0,0));
	}
	

	isAttacking = false;
	_target = nullptr;


}

void CannonTypeHook::pause()
{
	Cannon::pause();
	_readyBullet->pause();
	_handle->pause();
}

void CannonTypeHook::resume()
{
	Cannon::resume();
	_readyBullet->resume();
	_handle->resume();
}


void CannonTypeHook::setDirection()
{

	if (_handle->getScaleY() > 1.2 )
	{
		return;
	}
	Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
	_center->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
}



Enemy* CannonTypeHook::getCatchingTarget()
{
	return _target;
}



void CannonTypeHook::catchOnce( bool catching , Point targetPosition)
{
	Point p = _target->getPosition();
	float dis = getPosition().getDistance(p) - 20;

	_readyBullet->stopAllActions();
	_handle->stopAllActions();
	_readyBullet->setPosition(Point(0,0));
	_handle->setPosition(Point(0,0));
	_handle->setScale(4,1);

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_hook.mp3");

	if (catching)
	{
		
		Vec2 mv_tar_dir = targetPosition - _target->getPosition(); 
		float mv_tar_dur = mv_tar_dir.length() * 0.1 / dis;
		
		auto dt_tar = DelayTime::create(0.1f);
		auto mv_tar = MoveBy::create(mv_tar_dur,mv_tar_dir);
		auto mv_updt = CallFunc::create([&]{

			_target->updateDestination();
// 			float damageContributed = _target->onPhysicalDamaged(100);
// 			DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);


		});
		auto seq = Sequence::create(dt_tar,mv_tar,mv_updt,NULL);

		_target->setBuff(BuffTypeStun::create(_target,0.1f + mv_tar_dur));
		//_target->setBuff(BuffTypeBlooding::create(_target,0.1f + mv_tar_dur));

		_target->runAction(seq);

		
		

	}



	//bullet->setTarget(_target);

	auto st = CallFunc::create([&](){

		if (_target != nullptr)
		{
			BulletTypeHook* bullet = BulletTypeHook::create();
			bullet->setPosition(getPosition());
			bullet->setRotation(getRotation());
			bullet->setDamage(_damage, catching);
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

	



	isAttacking = false;
	_target = nullptr;
}

