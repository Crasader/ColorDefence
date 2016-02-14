#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SoundManager.h"

class Cannon : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(Cannon);


	unsigned getCannonType();
	void setCannonType(unsigned type);



	virtual void tryGetTarget();
	virtual bool getAttackingState();

	float attackRange;

	virtual void setColorInfo(cocos2d::Color3B c3b);


	cocos2d::Color3B getColorInfo();

	bool hasExtraState;
	bool extraStateOn;
	virtual void setExtraState(bool on);

	bool canBeBoosted;
	float boostFactor;
	bool isBoosted;
	

	bool hasBaseAfterDestroyed;


	bool isActioning();


	virtual void pause();
	virtual void resume();


protected:
	
	bool _isActioning;

	bool isAttacking;

	unsigned _cannonType;

	bool readyToShoot;

	

	EnemyManager* em;


	float _damage;
	int _attackInterval;


	Enemy* _target;

	virtual void update(float delta);

	virtual void setDirection();

	virtual void attackOnce();

	int _iterator;

	virtual void onExit();



};



