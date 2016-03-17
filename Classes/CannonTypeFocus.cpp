#include "CannonTypeFocus.h"
#include "BulletTypeFocus.h"
#include "NumericalManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

bool CannonTypeFocus::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Focus_base.png");
	setRotation(180);

	_sight = Sprite::create("cannons/CannonCover_Focus_sight.png");
	addChild(_sight);
	_sight->setPosition((Vec2)getContentSize()/2 );

	_barrel = Sprite::create("cannons/CannonCover_Focus_barrel.png");
	addChild(_barrel);
	_barrel->setPosition((Vec2)getContentSize()/2 );
	_barrel->setVisible(false);

	_hasSight = false;



	//监听“敌人将要到达终点”的事件
	auto listenerEnemyWillArrive = EventListenerCustom ::create("ENEMY_WILL_ARRIVE",[&](EventCustom* event){
		
		Enemy* e = static_cast<Enemy*>(event->getUserData());

		if ((nullptr!=_target)&&(e==_target)&&(isActioning()))
		{
			sacrifice();
			
		}

	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEnemyWillArrive,this);


	return true;
}




void CannonTypeFocus::attackOnce()
{


	BulletTypeFocus* bullet = BulletTypeFocus::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, !_hasSight);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);



	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_focus.mp3");

	if (!_hasSight)
	{
		bullet->setColor(NumericalManager::getInstance()->getBulletColor(getColorInfo()));
		_hasSight = true;
		_sight->setVisible(false);
		_barrel->setVisible(true);
	}





}

void CannonTypeFocus::update( float delta )
{
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
		_target = nullptr;
		resetSight();
		return;
	}

	//若正在攻击
	if (isAttacking)
	{


		//若攻击对象死了
		if ((!_target->isAlive())||(_target->isFloating)||((!_hasSight)&&(this->getPosition().getDistance(_target->getPosition())>attackRange)))
		{
			isAttacking = false;
			_target = nullptr;
			resetSight();
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

void CannonTypeFocus::sacrifice()
{

	int color_r = NumericalManager::getInstance()->getResourceByColor(getColorInfo().r);
	int color_g = NumericalManager::getInstance()->getResourceByColor(getColorInfo().g);
	int color_b = NumericalManager::getInstance()->getResourceByColor(getColorInfo().b);
	if ((color_r == 1)&&(color_g == 1)&&(color_b == 1))
	{

	}
	else
	{

		//粒子系统 特效
		auto emitter_1 = ParticleSystemQuad::create("effects/Particle_Sacrifice.plist");
		auto emitter_2 = ParticleSystemQuad::create("effects/Particle_Sacrifice.plist");
		auto emitter_3 = ParticleSystemQuad::create("effects/Particle_Consumer.plist");

		emitter_1->setPosition(getPosition());
		emitter_2->setPosition(_target->getPosition());
		emitter_3->setPosition(getPosition());
		(getParent())->addChild(emitter_1);
		(getParent())->addChild(emitter_2);
		(getParent())->addChild(emitter_3,10086);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter_1);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter_2);
		ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter_3);

 		Vec2 dir = emitter_1->getPosition() - emitter_2->getPosition();
		float l = dir.length();
 		dir.normalize();
// 		emitter_1->setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.x, - dir.y)) - 90);
// 		emitter_2->setRotation(CC_RADIANS_TO_DEGREES(atan2(dir.x, - dir.y)) - 90);
		emitter_1->runAction(MoveBy::create(0.24,dir*l*(-0.6)));
		emitter_2->runAction(MoveBy::create(0.2,dir*l*0.6));


		
		



		//SoundManager::getInstance()->playSoundEffect("sound/bullet_explode_producer.wav");


		float dmg = (float)( color_r + color_g + color_b );
		dmg = dmg*dmg*18;
		for (Enemy* e:EnemyManager::getInstance()->enemiesInSequence)
		{
			if (e->getPosition().getDistance(_target->getPosition())<125)
			{
				e->onPhysicalDamaged(dmg);
			}
		}
		int c = NumericalManager::getInstance()->getColorByResource(1);
		setColorInfo(Color3B(c,c,c));

	}


	isAttacking = false;
	_target = nullptr;


}



void CannonTypeFocus::resetSight()
{
	if (!_hasSight)
	{
		return;
	}
	_sight->setVisible(true);
	_sight->setRotation(0);
	_hasSight = false;
	_sight->stopAllActions();
	_sight->setScale(0.01);
	_sight->runAction(ScaleTo::create(0.2,1));
	_barrel->setVisible(false);
}





void CannonTypeFocus::setDirection()
{
	if (!_hasSight)
	{
		Point normalized = ccpNormalize(ccp(_target->getPosition().x - getPosition().x,	_target->getPosition().y - getPosition().y));
		setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) + 90);
	}
	else
	{
		Cannon::setDirection();
	}
	
}

void CannonTypeFocus::setColorInfo( cocos2d::Color3B c3b )
{
	Cannon::setColorInfo(c3b);
	_sight->setColor(c3b);
}

void CannonTypeFocus::pause()
{
	Cannon::pause();
	_sight->pause();
}

void CannonTypeFocus::resume()
{

	_sight->resume();
	Cannon::resume();
}

