#pragma once

#include "cocos2d.h"
#include "Buff.h"

class BuffTypeSlow : public Buff
{
public:

	//��ʼ��
	virtual bool init(Enemy* enemy, float slowFactor ,float slowTime);  

	//create����
	static BuffTypeSlow* create(Enemy* enemy, float slowFactor ,float slowTime);

	virtual void makeEffectWithTarget(Enemy* target);

	virtual void overrideWithNewBuff(Buff* newBuff);


	virtual void setAppearacneWithTarget(Enemy* target , bool show);

private:


	float _slowFactor;

};

