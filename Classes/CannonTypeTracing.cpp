#include "CannonTypeTracing.h"
#include "BulletTypeTracing.h"
#include "NumericalManager.h"


const int color_tag = 111;
USING_NS_CC;

bool CannonTypeTracing::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Tracing_base.png");
	//getChildByTag(color_tag)->setVisible(false);
	
	_gate = Sprite::create("cannons/CannonCover_Tracing_gate.png");
	addChild(_gate,-2);
	_gate->setPosition(getContentSize().width/2 , getContentSize().height/2 - 17 );
	//_gate->setVisible(false);
	_gate->setAnchorPoint(Point(0.5,0.311));

	_gateColor = Sprite::create("cannons/CannonCover_Tracing_gateColor.png");
	_gate->addChild(_gateColor,10);
	_gateColor->setPosition(_gate->getContentSize()/2);
	//_gateColor->setVisible(false);

	((Sprite*)getChildByTag(color_tag))->setTexture("cannons/CannonCover_Tracing_baseColor.png");
	((Sprite*)getChildByTag(color_tag))->setLocalZOrder(10086);
	





	return true;
}




void CannonTypeTracing::attackOnce()
{

	_gate->stopAllActions();
	_gate->setScale(1);


	auto st1 = ScaleTo::create(0.05,1,0.2);
	auto dt = DelayTime::create(0.2);
	auto st2 = ScaleTo::create(0.15,1,1);

	_gate->runAction(Sequence::create(st1,dt,st2,NULL));


	BulletTypeTracing* bullet = BulletTypeTracing::create();
	bullet->setPosition(getPosition());
	
	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	bullet->setRotation(getRotation());
	bullet->setDamageContributerID(_damageContributerID);
	bullet->setDamage(_damage, 180.0, 90.0, 540.0 , 3*_damage );

	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);
	
	


	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_tracing.mp3");

	isAttacking = false;
	_target = nullptr;


}

void CannonTypeTracing::pause()
{
	Cannon::pause();
	_gate->pause();


}

void CannonTypeTracing::resume()
{
	Cannon::resume();
	_gate->resume();


}

void CannonTypeTracing::setColorInfo( cocos2d::Color3B c3b )
{
	(this->getChildByTag(color_tag))->setColor(c3b);
	_gateColor->setColor(c3b);



	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);

}


void CannonTypeTracing::setDirection()
{
	if (_gate->getScaleY()<0.8)
	{
		return;
	}
	Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
	setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) - 90);
}