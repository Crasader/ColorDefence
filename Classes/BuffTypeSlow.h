#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeSlow : public Buff
{
public:

	//初始化
	virtual bool init(Enemy* enemy, float slowFactor ,float slowTime);  

	//create函数
	static BuffTypeSlow* create(Enemy* enemy, float slowFactor ,float slowTime);

	virtual void makeEffectWithTarget(Enemy* target, float delta);

	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);

private:


	float _slowFactor;

};

