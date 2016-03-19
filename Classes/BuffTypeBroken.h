#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeBroken : public Buff
{
public:


	//³õÊ¼»¯
	virtual bool init(Enemy* enemy, float brokenValue ,float brokenTime , bool accumulate);  

	//createº¯Êý
	static BuffTypeBroken* create(Enemy* enemy, float brokenValue ,float brokenTime , bool accumulate);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);


	bool verifyWithTarget(Enemy* target);


	bool canAccumulate();

protected:

	bool _accumulate;

	float _brokenValue;

};

