#pragma once

#include "cocos2d.h"
#include "HitPointBar.h"
#include "Buff.h"

//class Buff;

class Enemy : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(Enemy);

	void setEnemyType(int enemyType);


	void onSuperPowerDamage(float damage );
	void onRealDamaged( float damage );
	void onPhysicalDamaged( float damage );
	void onMagicalDamaged( float damage );
	void onShadowDamaged( float damage );



	//new
	bool setBuff(Buff* buff);
	void setSpeedFactor(float speedFactor);
	void setArmorLose(float brokenValue);
	void setStun(bool stun);
	void setPoisoningState(bool hasBuffPoisoning);
	void setSuperPoisoningState(bool hasBuffSuperPoisoning);
	bool hasBuffPoisoning();
	bool hasBuffSuperPoisoning();
	void setSpreadDamageState(bool hasBuffSpreadDamage);
	bool hasBuffSpreadDamage();


	bool isMoving();

	bool isAlive();
	
	//关于不同种类怪
	virtual bool isAntiMagic();
	virtual bool isBoss();
	virtual bool hasArmor();
	int getArmor();


	int currentDestination;

	float getMovingProgress();

	//移动速度
	float moveSpeed;


	//抖动
	void shake();

	//死亡
	virtual void onDeath();

	//等待间隔
	int timeInterval;


	//new
	void solveBuff();

	//区分是敌人 还是敌人间隔
	bool isRealEnemy;

	void willArrive();

	



	void hideHitPointBar();

	void setFloating();
	bool isFloating;



	virtual void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	void setMoveDirection(cocos2d::Vec2 direction);

	cocos2d::Sprite* getAppearance();
	cocos2d::Sprite* getEquipment();

	//装备上的粒子系统
	cocos2d::ParticleSystem* particles;

	virtual void pause();
	virtual void resume();


	float getRestHitPointRate();


	int chancesCost();

protected:

	int _enemyType;

	int _chancesCost;

	//护甲
	float _armor;
	float _armorFull;

	//生命值
	float _hitPoint;
	float _fullHitPoint;
	HitPointBar* hpb;


	float _moveSpeedFull;


private:

	void setInactive();


	//enemy的显示图片
	cocos2d::Sprite* _appearance;
	//enemy的装备
	cocos2d::Sprite* _equipment;





	//buff相关
	//new
	cocos2d::Vector<Buff*> _buffs;
	bool _hasBuffStun;
	bool _hasBuffPoisoning;
	bool _hasBuffSuperPoisoning;
	bool _hasBuffSpreadDamage;


};

