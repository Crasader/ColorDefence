#include "CannonTypeDuplicate.h"
#include "BulletTypeDuplicate.h"
#include "NumericalManager.h"
#include "CannonManager.h"
#include "ParticleEmitterManager.h"

USING_NS_CC;

const int color_tag = 111;

bool CannonTypeDuplicate::init()
{

	if ( !Cannon::init() )
	{
		return false;
	}

	_cannonType = 0;
	setTexture("cannons/CannonCover_Duplicate.png");


	Sprite* bg = Sprite::create("cannons/CannonColor.png");
	addChild(bg,-10);
	bg->setPosition(getContentSize()/2);
	//bg->setScale(1.1);
	bg->setOpacity(190);

	getChildByTag(color_tag)->setVisible(false);

	return true;
}




void CannonTypeDuplicate::attackOnce()
{



	BulletTypeDuplicate* bullet = BulletTypeDuplicate::create();
	bullet->setPosition(getPosition());
	bullet->setRotation(getRotation());
	bullet->setDamage(_damage, 44);
	bullet->setDamageContributerID(_damageContributerID);

	bullet->setTarget(_target);
	getParent()->addChild(bullet);

	//
	bullet->setColor(getColorInfo());
	//

	SoundManager::getInstance()->playSoundEffect("sound/cannon_shot_duplicate.mp3");


	if (getColorInfo() == Color3B(255,255,255))
	{
		_eventDispatcher->dispatchCustomEvent("CANNON_DUPLICATE",this);
	}
	


}

void CannonTypeDuplicate::setColorInfo( cocos2d::Color3B c3b )
{
	(this->getChildByTag(color_tag))->setColor(c3b);

	NumericalManager* nm = NumericalManager::getInstance();

	attackRange = nm->getRangeByColor(c3b,_cannonType);
	_attackInterval = nm->getIntervalByColor(c3b , _cannonType);
	_damage = nm->getAttackByColor(c3b, _cannonType);

	setColor(c3b);
}

void CannonTypeDuplicate::duplicateAtPoint( cocos2d::Point point )
{

	CannonTypeDuplicate* cannon = CannonTypeDuplicate::create();

	getParent()->addChild(cannon);
	cannon->setPosition(getPosition());
	CannonManager::getInstance()->cannons.pushBack(cannon);
	cannon->hasBaseAfterDestroyed = false;
	cannon->setRotation(getRotation());
	cannon->_damageContributerID = _damageContributerID;
	
	
	//资源属性变化
	float color = NumericalManager::getInstance()->getColorByResource(8);
	cannon->setColorInfo(Color3B(color,color,color));
	setColorInfo(Color3B(color,color,color));

	//动画准备
	stopAllActions();
	setScale(1);
	cannon->setScale(0.01);


	//动画
	ScaleTo* st_1 = ScaleTo::create(0.2f,0.01f);
	ScaleTo* st_b_1 = ScaleTo::create(0.2f,1);
	Sequence* sq_1 = Sequence::create(st_1,st_b_1,NULL);
	runAction(sq_1);

	DelayTime* dt_2 = DelayTime::create(0.2f);
	ScaleTo* st_b_2 = ScaleTo::create(0.2f,1);
	MoveTo* mt_2 = MoveTo::create(0.2f,point);
	Spawn* sp_2 = Spawn::create(st_b_2,mt_2,NULL );
	Sequence* sq_2 = Sequence::create(dt_2,sp_2,NULL);
	cannon->runAction(sq_2);

	SoundManager::getInstance()->playSoundEffect("sound/cannon_duplicate.mp3");

	//粒子系统 特效
	ParticleSystem* emitter = ParticleSystemQuad::create("effects/Particle_Duplicate.plist");
	(getParent())->addChild(emitter,10086);
	emitter->setPosition(getPosition());
	ParticleEmitterManager::getInstance()->particleEmitters.pushBack(emitter);

	DelayTime* dt_3 = DelayTime::create(0.1f);
	MoveTo* mt_3 = MoveTo::create(0.3f,point);
	Sequence* sq_3 = Sequence::create(dt_3,mt_3,NULL);
	emitter->runAction(sq_3);

}

