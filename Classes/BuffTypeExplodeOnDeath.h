#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeExplodeOnDeath : public Buff
{
public:

	//��ʼ��
	virtual bool init(Enemy* enemy, float buffTime);  

	//create����
	static BuffTypeExplodeOnDeath* create(Enemy* enemy, float buffTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);

	virtual bool verifyWithTarget(Enemy* target);

	virtual void setAppearacneWithTarget(Enemy* target , bool show);

private:

};

