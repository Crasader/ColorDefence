#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SoundManager.h"

class Cannon : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
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



	void setDamageContributerID();

	

protected:


	cocos2d::Color3B _color;

	virtual void update(float delta);


	
	bool _isActioning;

	bool isAttacking;

	unsigned _cannonType;

	bool readyToShoot;

	

	EnemyManager* em;


	float _damage;
	int _attackInterval;


	Enemy* _target;



	virtual void setDirection();

	virtual void attackOnce();

	float _iterator;

	virtual void onExit();




	int _damageContributerID;


};



