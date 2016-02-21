#include "CannonTypeProducer.h"
#include "NumericalManager.h"
#include "BulletTypeProducer.h"
#include "ParticleEmitterManager.h"
#include "ResourceManager.h"

USING_NS_CC;
const int color_tag = 111;

const int attacksPerProduce = 8;

const float gear_distance = 20.74;

bool CannonTypeProducer::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}


	for (int i = 0 ; i<2 ; i++)
	{
		_gear[i] = Sprite::create("cannons/CannonCover_Producer_gear.png");
		addChild(_gear[i],i+1);
		Vec2 v = getContentSize();
		_gear[i]->setPosition(v.x/2 + (float)(i-0.5)* gear_distance,v.y/2);
		_gear[i]->setRotation((float)i * 22.5);

	}


	_cannonType = 0;
	setTexture("cannons/CannonCover_Producer_base.png");

	_attackCounter = 0;

	return true;
}




void CannonTypeProducer::attackOnce()
{



	BulletTypeProducer* bullet = BulletTypeProducer::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage);
	bullet->setDamageContributerID(_damageContributerID);


	bullet->setTarget(_target, getPosition());
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	_attackCounter++;
	if (_attackCounter >= attacksPerProduce)
	{
		_attackCounter=0;
		//粒子系统 特效
		ParticleSystem* emitter = ParticleSystemQuad::create("effects/Particle_Producer_getResource.plist");
		(getParent())->addChild(emitter,10086);
		emitter->setPosition(getPosition());
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);
		ResourceManager::getInstance()->bonus(1,1,1);
		
		SoundManager::getInstance()->playSoundEffect("sound/cannon_produce.mp3");
	}
	

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_producer.wav");

}

void CannonTypeProducer::setDirection()
{

	float dir = (this->getChildByTag(color_tag))->getRotation() + getRotation();

	Cannon::setDirection();

	(this->getChildByTag(color_tag))->setRotation(dir - getRotation());

	for (int i = 0 ; i<2 ; i++)
	{

		_gear[i]->setRotation(_gear[i]->getRotation()+ (i==0?3:-3));

	}

}




