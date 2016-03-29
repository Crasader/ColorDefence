#include "CannonTypeBounce.h"
#include "BulletTypeBounce.h"
#include "NumericalManager.h"

USING_NS_CC;

bool CannonTypeBounce::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Bounce_base.png");
	
	_gate = Sprite::create("cannons/CannonCover_Bounce_gate.png");
	addChild(_gate,10);
	_gate->setPosition(getContentSize().width/2 , getContentSize().height/2  + 25);

	_snow = ParticleSystemQuad::create("effects/Particle_Slow.plist");
	addChild(_snow,10);
	_snow->setPosition(getContentSize()/2);
	_snow->setTotalParticles(5);
	_snow->setEmissionRate(10);

	_bounceRange = 175;
	_damageReduceFactor = 1.1;
	_bounceTimes = 4;


	return true;
}




void CannonTypeBounce::attackOnce()
{

	_gate->stopAllActions();
	_gate->setScaleY(1);
	auto st1 = ScaleTo::create(0.2,1,0);
	auto st2 = ScaleTo::create(0.2,1,1);
	_gate->runAction(Sequence::create(st1,st2,nullptr));

	BulletTypeBounce* bullet = BulletTypeBounce::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, _bounceRange, _damageReduceFactor , _bounceTimes);
	bullet->setDamageContributerID(_damageContributerID);

	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);
	
	
	//
	//bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_bounce.wav");



}

void CannonTypeBounce::pause()
{
	Cannon::pause();
	_gate->pause();
	_snow->pause();
}

void CannonTypeBounce::resume()
{
	Cannon::resume();
	_gate->resume();
	_snow->resume();
}

