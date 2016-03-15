#include "BulletTypeFocus.h"
#include "EnemyManager.h"
#include "BulletManager.h"

USING_NS_CC;

bool BulletTypeFocus::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);

	setTexture("effects/Bullet_Focus.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_isSight = false;

	return true;
}



void BulletTypeFocus::explode()
{

	if (_isSight)
	{
		float damageContributed = _target->onPhysicalDamaged(_damage);
		DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

		setTexture("effects/Bullet_Focus_attacker.png");
		auto sp = Sprite::create("effects/Bullet_Focus_attackerCenter.png");
		addChild(sp);
		sp->setPosition(getContentSize()/2);
		runAction(RepeatForever::create(RotateBy::create(2,-180)));
		runAction(RepeatForever::create(Sequence::create(FadeOut::create(1),FadeIn::create(1),NULL)));
		
		schedule(schedule_selector(BulletTypeFocus::update), 1.0f/60.0f);
	}
	else
	{
		float damageContributed = _target->onPhysicalDamaged(_damage);
		DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);
		removeFromParent();
		BulletManager::getInstance()->bullets.eraseObject(this);
	}



}

void BulletTypeFocus::setDamage(float damage , bool isSight)
{
	_damage = damage;
	_isSight = isSight;

}

void BulletTypeFocus::update( float delta )
{

	if ((_target->isFloating)||(!_target->isAlive()))
	{
		unschedule(schedule_selector(BulletTypeFocus::update));
		removeFromParent();
		BulletManager::getInstance()->bullets.eraseObject(this);
		return;
	}
	setPosition(_target->getPosition());

}


