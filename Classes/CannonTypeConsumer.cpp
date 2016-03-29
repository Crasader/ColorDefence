#include "CannonTypeConsumer.h"
#include "BulletTypeConsumer.h"
#include "NumericalManager.h"
#include "ParticleEmitterManager.h"
#include "ResourceManager.h"

USING_NS_CC;
const int color_tag = 111;

bool CannonTypeConsumer::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	for (int i = 0 ; i<3 ; i++)
	{
		_mixer[i] = Sprite::create("cannons/CannonCover_Consumer_mixer.png");
		getChildByTag(color_tag)->addChild(_mixer[i],i+1);
		Vec2 v = getChildByTag(color_tag)->getContentSize();
		_mixer[i]->setPosition(v/2);
		_mixer[i]->setRotation((float)i * 120);

	}

	/*
	RotateBy* ro = RotateBy::create(1.0,-90);
	RepeatForever* rept = RepeatForever::create(ro);
	getChildByTag(color_tag)->runAction(rept);
	*/

	_cannonType = 0;
	setTexture("cannons/CannonCover_Consumer_base.png");

	
	//extra state 表示攻击模式开启
	hasExtraState = true;



	//for (int i = 0 ; i<3; i++)
	//{
	//	autoSupplyingLimit[i] = 0;
	//}
	
	_consumeCount = 0.0f;
	extraStateOn = false;
	//_texureWithExtraStateOn = false;

	_coverWhenClosed = Sprite::create("cannons/CannonCover_Consumer_closed.png"); 
	addChild(_coverWhenClosed);
	_coverWhenClosed->setPosition(getContentSize()/2);

	return true;
}




void CannonTypeConsumer::attackOnce()
{



	BulletTypeConsumer* bullet = BulletTypeConsumer::create();
	bullet->setPosition(getPosition());
	//bullet->setRotation(getRotation());
	bullet->setDamage(_damage,118);
	bullet->setDamageContributerID(_damageContributerID);

	
	getParent()->addChild(bullet);
	bullet->setTarget(_target);


	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//

	Color3B c3b = getColorInfo();
	int resource[3];
	resource[0]= NumericalManager::getInstance()->getResourceByColor(c3b.r);
	resource[1]= NumericalManager::getInstance()->getResourceByColor(c3b.g);
	resource[2]= NumericalManager::getInstance()->getResourceByColor(c3b.b);

	_consumeCount += resource[0] ;
	_consumeCount += resource[1] ;
	_consumeCount += resource[2] ;

	

	if (_consumeCount >80 )
	{
		_consumeCount-= 80;
		//粒子系统 特效
		ParticleSystem* emitter = ParticleSystemQuad::create("effects/Particle_Consumer.plist");
		(getParent())->addChild(emitter,10086);
		emitter->setPosition(getPosition());
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);

		SoundManager::getInstance()->playSoundEffect("sound/cannon_consume.mp3");
		
		
		for (int k = 0 ; k<3 ; k++)
		{

			if (ResourceManager::getInstance()->restResource[k]>0)
			{
				ResourceManager::getInstance()->restResource[k] -- ;
			}
			else
			{
				if (resource[k]>1)
				{
					resource[k]--;
				}
				
			}

		}


		


		setColorInfo(Color3B(
			NumericalManager::getInstance()->getColorByResource(resource[0]),
			NumericalManager::getInstance()->getColorByResource(resource[1]),
			NumericalManager::getInstance()->getColorByResource(resource[2])));
	}

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_consumer.mp3");


}

void CannonTypeConsumer::setColorInfo( cocos2d::Color3B c3b )
{
	(this->getChildByTag(color_tag))->setColor(c3b);

	_mixer[0]->setColor(Color3B(c3b.r,0,0));
	_mixer[1]->setColor(Color3B(0,c3b.g,0));
	_mixer[2]->setColor(Color3B(0,0,c3b.b));

	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);

// 	autoSupplyingLimit[0] = nm->getResourceByColor(c3b.r);
// 	autoSupplyingLimit[1] = nm->getResourceByColor(c3b.g);
// 	autoSupplyingLimit[2] = nm->getResourceByColor(c3b.b);

}



void CannonTypeConsumer::setDirection()
{

	//float dir = (this->getChildByTag(color_tag))->getRotation() + getRotation();
	//Cannon::setDirection();
	//(this->getChildByTag(color_tag))->setRotation(dir - getRotation() -2);

	(this->getChildByTag(color_tag))->setRotation((this->getChildByTag(color_tag))->getRotation() -2);

}

void CannonTypeConsumer::update( float delta )
{




	if (!extraStateOn)
	{
		return;
	}

	if (!readyToShoot)
	{
		_iterator++;
		if (_iterator>=_attackInterval)
		{
			readyToShoot = true;
			_iterator=0;
		}

	}


	if (em->enemiesInSequence.size()==0)
	{
		isAttacking = false;
		return;
	}

	//若正在攻击
	if (isAttacking)
	{


		//若攻击对象死了或超出范围
		if ((!_target->isAlive())||(this->getPosition().getDistance(_target->getPosition())>attackRange)||(_target->isFloating))
		{
			isAttacking = false;
			_target = nullptr;
			return;
		}

		setDirection();


		if (readyToShoot)
		{
			readyToShoot = false;
			attackOnce();

		}






	}
	//若不在攻击
	else
	{


		//如果有进入范围的
		tryGetTarget();

	}


}

void CannonTypeConsumer::setExtraState( bool on )
{

	Cannon::setExtraState(on);
	_coverWhenClosed->setVisible(!on);

}
