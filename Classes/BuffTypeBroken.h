#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeBroken : public Buff
{
public:


	//初始化
	virtual bool init(Enemy* enemy, float brokenValue ,float brokenTime , bool accumulate);  

	//create函数
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

