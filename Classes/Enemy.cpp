#include "Enemy.h"
#include "ActionShake.h"
#include "ParticleEmitterManager.h"
#include "ResourceManager.h"
#include "MapPointsManager.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "Buff.h"
#include "BuffTypeSpreadDamage.h"
#include "BuffTypeExplodeOnDeath.h"

const int actionShake_tag = 666;


USING_NS_CC;

bool Enemy::init()
{

	if ( !Sprite::init() )
	{
		return false;
	}

	_enemyType = 0;

	_chancesCost = 1;

	_appearance = Sprite::create("enemies/Enemy_01.png");
	_equipment = Sprite::create();
	
	addChild(_appearance);
	_appearance->addChild(_equipment);

	isRealEnemy = true;
	isFloating = false;

	particles = nullptr;



	//new
	_buffs = Vector<Buff*>() ;
	_hasBuffPoisoning = false;
	_hasBuffSuperPoisoning = false;
	_hasBuffStun = false;
	_hasBuffSpreadDamage = false;
	_hasBuffExplodeOnDeath = false;


	currentDestination = 0;



	timeInterval = 36;


	hpb = HitPointBar::create();
	addChild(hpb,1);
	hpb->setPosition(Point(0,_appearance->getContentSize().height / 2 + 10));
	hpb->setHitPoint(1.0);


	_moveDirection = Vec2(0,0);


	return true;
}



float Enemy::onRealDamaged( float damage )
{


	if (_hasBuffSpreadDamage)
	{
		((BuffTypeSpreadDamage*)(getChildByTag(Buff::kBuffTypeSpreadDamage)))->spreadDamage(getPosition());
	}

	float damageContribution = damage>_hitPoint?_hitPoint:damage;

	_hitPoint-= damage;

	if (_hitPoint<0)
	{
		_hitPoint = 0;
	}
	hpb->setHitPoint((float)_hitPoint/(float)_fullHitPoint);

	return damageContribution;

}

float Enemy::onPhysicalDamaged( float damage )
{


	if (isFloating||!isAlive())
	{
		return 0;
	}

	int realDamage = damage - _armor;
	if (realDamage<=1)
	{
		realDamage = 1;
	}

	return onRealDamaged(realDamage);

}


float Enemy::onMagicalDamaged( float damage )
{

	if (isFloating||!isAlive())
	{
		return 0;
	}

	if (isAntiMagic())
	{
		return 0;
	}

	return onRealDamaged(damage);
	
}



bool Enemy::isAlive()
{
	if (_hitPoint>0)
	{
		return true;
	}
	return false;
}



void Enemy::setEnemyParameter(int hp, float ms, float arm )
{



	_moveSpeedFull = ms;
	moveSpeed = _moveSpeedFull;

	//_armorFull = arm;
	_armorFull = 0;
	_armor = _armorFull;

	_fullHitPoint = hp;
	_hitPoint = _fullHitPoint;




}

void Enemy::hideHitPointBar()
{
	hpb->setVisible(false);
}

void Enemy::setFloating()
{

	SoundManager::getInstance()->playSoundEffect("sound/enemy_float.mp3");

	setInactive();




	setScale(3.0);
	_appearance->setOpacity(50);
	_equipment->setOpacity(20);
	_equipment->removeAllChildren();
	if (nullptr!=particles)
	{
		particles->setEmissionRate(0);
	}
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setPosition(origin.x + visibleSize.width * CCRANDOM_0_1() ,
		origin.y + visibleSize.height * CCRANDOM_0_1()
		);


	isFloating = true;

}


void Enemy::shake()
{

	return;

	if (isAntiMagic())
	{
		return;
	}
	ActionShake* shake = ActionShake::create(0.12,10);
	shake->setTag(actionShake_tag);
	if (nullptr == getActionByTag(actionShake_tag))
	{
		runAction(shake);

	}
}

void Enemy::onDeath()
{

	if (_hasBuffExplodeOnDeath)
	{
		

		((BuffTypeExplodeOnDeath*)(getChildByTag(Buff::kBuffTypeExplodeOnDeath)))->explodeOnDeath(getPosition());

	}

	setInactive();
	FadeOut* fo = FadeOut::create(0.5);
	_appearance->runAction(fo);

	ScaleTo* st = ScaleTo::create(0.75,0);
	_equipment->runAction(st);
	_equipment->removeAllChildren();

	if (isBoss())
	{
		for (int i = 0; i < 10; i++)
		{
			ResourceManager::getInstance()->bonus(1);
		}
		
	}
	else
	{
		ResourceManager::getInstance()->bonus(1);
	}

	SoundManager::getInstance()->playSoundEffect("sound/enemy_die.mp3");

}

void Enemy::setMoveDirection( cocos2d::Vec2 direction )
{

	//行走时 需要调整面向的方向
	_moveDirection = direction;
	_moveDirection.normalize();
	_appearance->setRotation(CC_RADIANS_TO_DEGREES(atan2(_moveDirection.y, - _moveDirection.x)) + 90);


}

cocos2d::Sprite* Enemy::getAppearance()
{
	return _appearance;
}

cocos2d::Sprite* Enemy::getEquipment()
{
	return _equipment;
}

void Enemy::pause()
{
	Sprite::pause();
	_equipment->pause();
	_appearance->pause();
	if ((_equipment->getChildren()).empty())
	{
		return;
	}
	else
	{
		for (Node* n : _equipment->getChildren())
		{
			n->pause();
		}
	}
}

void Enemy::resume()
{
	Sprite::resume();
	_equipment->resume();
	_appearance->resume();
	if (_equipment->getChildren().empty())
	{
		return;
	}
	else
	{
		for (Node* n : _equipment->getChildren())
		{
			n->resume();
		}
	}
}

bool Enemy::isAntiMagic()
{
	return false;
}

bool Enemy::isBoss()
{

	return false;
}

int Enemy::getArmor()
{
	return _armor;
}



bool Enemy::isMoving()
{
	return !_hasBuffStun;
}



void Enemy::setInactive()
{
	//清除buff
	//new
	for (Buff* b : _buffs)
	{
		b->setAppearacneWithTarget(this,false);
	}
	_buffs.clear();




	if (_equipment != nullptr)
	{
		_equipment->stopAllActions();
	}


	
	if (nullptr!=particles)
	{
		particles->setEmissionRate(0);
		particles->setTotalParticles(0);
		ParticleEmitterManager::getInstance()->particleEmitters.eraseObject(particles);
		ParticleEmitterManager::getInstance()->emittersToRemove.pushBack(particles);
	}

	hideHitPointBar();

}

float Enemy::getMovingProgress()
{


	std::vector<Point> path = std::vector<Point>();
	LevelManager* lm = LevelManager::getInstance();
	for (int i= 0; i <lm->getEnemyPath().size()  ; i++)
	{
		path.push_back(MapPointsManager::getPointByIndex(lm->getEnemyPath().at(i))); 
	}


	
	float mp = getPosition().getDistance(path.at(currentDestination - 1));

	for (int i = 0 ; i< currentDestination -1 ; i++)
	{
		mp += path.at(i).getDistance(path.at(i+1));
	}

	return mp;

}

float Enemy::onShadowDamaged( float damage )
{
	if (isFloating||!isAlive())
	{
		return 0;
	}

	if (isAntiMagic())
	{
		damage = damage * 2;
	}
	else
	{
		damage = damage * 0.5;

	}

	return onRealDamaged(damage);

}

float Enemy::getRestHitPointRate()
{
	return (float)_hitPoint/(float)_fullHitPoint;
}

void Enemy::onSuperPowerDamage( float damage )
{
	
	auto act1 = DelayTime::create(0.05);
	
	auto act2 = CallFunc::create([&,damage](){

		onRealDamaged(damage/20);
		
	});

	runAction(Repeat::create(Sequence::create(act1,act2,NULL),20));


}

void Enemy::setEnemyType( int enemyType )
{
	_enemyType = enemyType;
}

void Enemy::willArrive()
{
	_eventDispatcher->dispatchCustomEvent("ENEMY_WILL_ARRIVE",this);
}

bool Enemy::hasArmor()
{
	return false;
}

int Enemy::chancesCost()
{
	return _chancesCost;
}


bool Enemy::setBuff( Buff* buff )
{

	if (!buff->verifyWithTarget(this))
	{
		return false;
	}
	


	for (Buff* b : _buffs)
	{
		if (b->getBuffType() == buff->getBuffType())
		{
			b->overrideWithNewBuff(buff);
			return true;
		}
	}
	


	_buffs.pushBack(buff);
	addChild(buff);
	buff->setTag(buff->getBuffType());
	buff->setAppearacneWithTarget(this,true);
	
	return true;
}

void Enemy::solveBuff()
{
	
	if (_buffs.empty())
	{
		return;
	}
 	int l  = _buffs.size()-1;
 	for (int i = l ; i>=0; i--)
 	{
 		_buffs.at(i)->makeEffectWithTarget(this);
 		if (_buffs.at(i)->willEndBuff())
 		{
			_buffs.at(i)->setAppearacneWithTarget(this,false);
			_buffs.at(i)->removeFromParent();
			_buffs.eraseObject(_buffs.at(i));
			

 		}
 	}





}

void Enemy::setSpeedFactor( float speedFactor )
{
	moveSpeed = _moveSpeedFull*speedFactor;
}

void Enemy::setStun( bool stun )
{
	_hasBuffStun = stun;
}

void Enemy::setArmorLose( float brokenValue )
{
	_armor = _armorFull - brokenValue;
	if (_armor < 0)
	{
		_armor = 0;
	}
}



void Enemy::setPoisoningState( bool hasBuffPoisoning )
{
	_hasBuffPoisoning = hasBuffPoisoning;
}

bool Enemy::hasBuffPoisoning()
{
	return _hasBuffPoisoning;
}

bool Enemy::hasBuffSuperPoisoning()
{
	return _hasBuffSuperPoisoning;

}

void Enemy::setSuperPoisoningState( bool hasBuffSuperPoisoning )
{
	_hasBuffSuperPoisoning = hasBuffSuperPoisoning;

	if (_hasBuffPoisoning&&_hasBuffSuperPoisoning)
	{

		for (Buff* b:_buffs)
		{
			if (b->getBuffType() == Buff::kBuffTypePoisoning)
			{
				b->forceEnd();
				return;
			}
		}
	}

}

void Enemy::setSpreadDamageState( bool hasBuffSpreadDamage )
{
	_hasBuffSpreadDamage = hasBuffSpreadDamage;
}

bool Enemy::hasBuffSpreadDamage()
{
	return _hasBuffSpreadDamage;
}

void Enemy::setBuffExplodeOnDeathState( bool hasBuffExplodeOnDeath )
{
	_hasBuffExplodeOnDeath = hasBuffExplodeOnDeath;
}

void Enemy::updateDestination()
{

}

void Enemy::move()
{

}

cocos2d::Vec2 Enemy::getMoveDirection()
{
	return _moveDirection;
}






