#pragma once

#include "cocos2d.h"







class Enemy;

class Buff : public cocos2d::Sprite
{
public:

	//³õÊ¼»¯
	virtual bool init();  

	//createº¯Êý
	CREATE_FUNC(Buff);

	unsigned getBuffType();

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	bool willEndBuff();

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);


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



protected:

	bool _end;

	unsigned _buffType;

	//Enemy* _target;

	float _buffTimeRest;

};

