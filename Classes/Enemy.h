#pragma once

#include "cocos2d.h"
#include "HitPointBar.h"
#include "Buff.h"

//class Buff;

class Enemy : public cocos2d::Sprite
{
public:

	//��ʼ��
	virtual bool init();  

	//create����
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
	
	//���ڲ�ͬ�����
	virtual bool isAntiMagic();
	virtual bool isBoss();
	virtual bool hasArmor();
	int getArmor();


	int currentDestination;

	float getMovingProgress();

	//�ƶ��ٶ�
	float moveSpeed;


	//����
	void shake();

	//����
	virtual void onDeath();

	//�ȴ����
	int timeInterval;


	//new
	void solveBuff();

	//�����ǵ��� ���ǵ��˼��
	bool isRealEnemy;

	void willArrive();

	



	void hideHitPointBar();

	void setFloating();
	bool isFloating;



	virtual void setEnemyParameter(int hitPoint, float moveSpeed, float armor);


	void setMoveDirection(cocos2d::Vec2 direction);

	cocos2d::Sprite* getAppearance();
	cocos2d::Sprite* getEquipment();

	//װ���ϵ�����ϵͳ
	cocos2d::ParticleSystem* particles;

	virtual void pause();
	virtual void resume();


	float getRestHitPointRate();


	int chancesCost();

protected:

	int _enemyType;

	int _chancesCost;

	//����
	float _armor;
	float _armorFull;

	//����ֵ
	float _hitPoint;
	float _fullHitPoint;
	HitPointBar* hpb;


	float _moveSpeedFull;


private:

	void setInactive();


	//enemy����ʾͼƬ
	cocos2d::Sprite* _appearance;
	//enemy��װ��
	cocos2d::Sprite* _equipment;





	//buff���
	//new
	cocos2d::Vector<Buff*> _buffs;
	bool _hasBuffStun;
	bool _hasBuffPoisoning;
	bool _hasBuffSuperPoisoning;
	bool _hasBuffSpreadDamage;


};

