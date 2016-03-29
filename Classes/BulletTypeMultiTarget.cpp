#include "BulletTypeMultiTarget.h"
#include "BulletManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool BulletTypeMultiTarget::init()
{

	if ( !Bullet::init() )
	{
		return false;
	}

	//BulletManager::getInstance()->bullets.pushBack(this);


	setTexture("effects/Effects_triangle.png");


	RotateBy* rot = RotateBy::create(0.1f,500);
	RepeatForever* rept = RepeatForever::create(rot);
	runAction(rept);


	Sprite* cover = Sprite::create("effects/Effects_triangle.png");
	cover->setScale(1,0.25);
	addChild(cover);
	cover->setPosition(getContentSize().width/2,getContentSize().height/6);


	return true;
}



void BulletTypeMultiTarget::explode()
{

	float damageContributed = _target->onMagicalDamaged(_damage);
	DamageContributionManager::getInstance()->recordContribution(_damageContributerID , damageContributed);

	
	unscheduleUpdate();

	removeFromParent();
	BulletManager::getInstance()->bullets.eraseObject(this);

}



void BulletTypeMultiTarget::setTarget( Enemy* enemy )
{
	_target = enemy;


	scheduleUpdate();



}

void BulletTypeMultiTarget::update( float delta )
{

	if ((_target->isFloating)||(!_target->isAlive()))
	{
		explode();
		return;
	}
			


	Vec2 dir = _target->getPosition() - getPosition();
	dir.normalize();
	//setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.y, - dir.x)) - 90);
	dir = 6.8*dir;
	setPosition(getPosition()+dir);
	




	if (getPosition().getDistance(_target->getPosition())<20)
	{
		explode();
	}


}
