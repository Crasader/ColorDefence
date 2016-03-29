#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeStun : public Buff
{
public:

	//初始化
	virtual bool init(Enemy* enemy, float stunTime);  

	//create函数
	static BuffTypeStun* create(Enemy* enemy, float stunTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);

private:

};

