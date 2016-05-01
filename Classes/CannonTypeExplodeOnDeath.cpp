#include "CannonTypeExplodeOnDeath.h"
#include "BulletTypeExplodeOnDeath.h"
#include "NumericalManager.h"


USING_NS_CC;
const int color_tag = 111;

bool CannonTypeExplodeOnDeath::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_ExplodeOnDeath_base.png");
	
	((Sprite*)getChildByTag(color_tag))->setTexture("cannons/CannonCover_ExplodeOnDeath_ring.png");

	_head = Sprite::create("cannons/CannonCover_ExplodeOnDeath_head.png");
	addChild(_head,-1);
	_head->setPosition(getContentSize()/2);

	Sprite* bg = Sprite::create("cannons/CannonColor.png");
	addChild(bg,-10086);
	bg->setPosition(getContentSize()/2);
	bg->setColor(Color3B(0,0,0));


	_particle = ParticleSystemQuad::create("effects/Particle_ExplodeOnDeath_buff.plist");
	addChild(_particle,10);
	_particle->setPosition(getContentSize()/2);
	_particle->setSpeed(45);
	_particle->setSpeedVar(0);
	_particle->setStartSize(10);
	_particle->setTotalParticles(150);
	_particle->setEmissionRate(150);
	_particle->setLife(0.45);



	return true;
}




void CannonTypeExplodeOnDeath::attackOnce()
{

	BulletTypeExplodeOnDeath* bullet = BulletTypeExplodeOnDeath::create();


	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 250 , 115.0 + 120.0 * (float) _color.r / 255);
	bullet->setDamageContributerID(_damageContributerID);


	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//
	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_eod.mp3");

	_head->stopAllActions();
	_head->setScale(2,1);
	_head->runAction(ScaleTo::create(0.2,1));


	isAttacking = false;
	_target = nullptr;


}

void CannonTypeExplodeOnDeath::pause()
{
	Cannon::pause();
	_particle->pause();
	_head->pause();

}

void CannonTypeExplodeOnDeath::resume()
{
	Cannon::resume();
	_particle->resume();
	_head->resume();

}

void CannonTypeExplodeOnDeath::setColorInfo( cocos2d::Color3B c3b )
{
	Cannon::setColorInfo(c3b);
	//setColor(c3b);
}

