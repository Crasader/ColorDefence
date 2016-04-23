#include "CannonTypeSpiral.h"
#include "BulletTypeSpiral.h"
#include "NumericalManager.h"
#include "ParticleEmitterManager.h"
#include "SoundManager.h"

USING_NS_CC;

bool CannonTypeSpiral::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Spiral.png");
	setOpacity(0);
	

	_inner = Sprite::create("cannons/CannonCover_Spiral_inner.png");
	addChild(_inner,3);
	_inner->setPosition(getContentSize()/2);

	_outter = Sprite::create("cannons/CannonCover_Spiral_outter.png");
	addChild(_outter,3);
	_outter->setPosition(getContentSize()/2);
	_outter->setOpacity(150);



	hasExtraState = true;
	extraStateOn = false;

	return true;
}




void CannonTypeSpiral::attackOnce()
{



	BulletTypeSpiral* bullet = BulletTypeSpiral::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, attackRange , extraStateOn);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
	//


	


	//充能 释放
	Color3B c3b = getColorInfo();
	int resource[3];
	resource[0]= NumericalManager::getInstance()->getResourceByColor(c3b.r);
	resource[1]= NumericalManager::getInstance()->getResourceByColor(c3b.g);
	resource[2]= NumericalManager::getInstance()->getResourceByColor(c3b.b);
















	if (extraStateOn)
	{

		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_spiral_on.mp3");
		_outter->stopAllActions();
		_outter->setScale(0.8);
		_outter->runAction(ScaleTo::create(_attackInterval/60.0,1));
		


		for (int k = 0 ; k<3 ; k++)
		{
			if (resource[k]>1)
			{
				resource[k]--;
			}
		}
	}
	else
	{


		SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_spiral.mp3");
		_outter->stopAllActions();
		_outter->setScale(1);
		auto act1 = ScaleTo::create(_attackInterval/60.0,0.8);
		auto act2 = CallFunc::create([&](){ _outter->setScale(1); });
		auto seq = Sequence::create(act1,act2,NULL);
		_outter->runAction(seq);



		//如果满了 粒子特效
		if (getColorInfo() == Color3B(255,255,255))
		{

			//粒子系统 特效
			ParticleSystem* emitter =  ParticleSystemQuad::create("effects/Particle_Spiral_full.plist");
			SoundManager::getInstance()->playSoundEffect("sound/cannon_spiral_full.mp3");


			(getParent())->addChild(emitter,10086);
			emitter->setPosition(getPosition());
			ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);



		}
		else
		//没满 加一个资源
		{
			int i = CCRANDOM_0_1()*3;
			for (int k = 0 ; k<3 ; k++)
			{
				if (resource[k]<resource[i])
				{
					i = k;
				}
			}
			if (resource[i]<16)
			{
				resource[i]++;
			}
		}







	}
	
	//更新颜色
	setColorInfo(Color3B(
		NumericalManager::getInstance()->getColorByResource(resource[0]),
		NumericalManager::getInstance()->getColorByResource(resource[1]),
		NumericalManager::getInstance()->getColorByResource(resource[2])));






}

void CannonTypeSpiral::setDirection()
{

	_inner->setRotation(_inner->getRotation()+(extraStateOn?12:-6));
	_outter->setRotation(_outter->getRotation()+(extraStateOn?-2:1));

}

void CannonTypeSpiral::setExtraState( bool on )
{

	Cannon::setExtraState(on);

	setColorInfo(getColorInfo());

	_outter->setOpacity(on?255:150);

}

void CannonTypeSpiral::pause()
{
	Cannon::pause();
	_outter->pause();
}

void CannonTypeSpiral::resume()
{
	Cannon::resume();
	_outter->resume();
}

