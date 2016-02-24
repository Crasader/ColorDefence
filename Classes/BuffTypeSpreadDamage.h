#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeSpreadDamage : public Buff
{
public:

	//³õÊ¼»¯
	virtual bool init(Enemy* enemy, float buffTime);  

	//createº¯Êý
	static BuffTypeSpreadDamage* create(Enemy* enemy, float buffTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);

	void spreadDamage(cocos2d::Point position);

private:

};

