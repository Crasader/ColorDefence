#pragma once

#include "cocos2d.h"







class Enemy;

class Buff : public cocos2d::Sprite
{
public:

	//初始化
	virtual bool init();  

	//create函数
	CREATE_FUNC(Buff);

	unsigned getBuffType();

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	bool willEndBuff();

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);

	void setDamageContributerID(int ID);


	enum BuffType
	{
		kBuffTypeSlow,
		kBuffTypePoisoning,
		kBuffTypeBroken,
		kBuffTypeStun,
		kBuffTypeSuperPoisoning,
		kBuffTypeSpreadDamage,
		kBuffTypeExplodeOnDeath,
		
		kBuff

	};

	void forceEnd();

protected:

	bool _end;

	unsigned _buffType;

	//Enemy* _target;

	float _buffTimeRest;


	int _damageContributerID;

};

